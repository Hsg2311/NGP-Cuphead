#include "Network.hpp"
#include "protocol.hpp"
#include "SendingStorage.hpp"
#include "Timer.hpp"
#include "PacketQueue.hpp"
#include "LogPacketQueue.hpp"

#include <iostream>
#include <thread>
#include <array>
#include <vector>
#include <atomic>
#include <chrono>
#include <queue>

#include <ranges>
#include <algorithm>

using Clock = std::chrono::high_resolution_clock;
using Seconds = std::chrono::duration<float>;
inline constexpr Seconds operator""_s( unsigned long long _Val ) noexcept {
	return Seconds( static_cast<float>( _Val ) );
}

std::array<network::TcpSocket*, 2> clients;
std::vector<std::thread> recvThreads;

std::atomic<bool> serverRun = true;

std::mutex packetQueueMtx;
std::mutex sockMtx;

// accept랑 send는 서버가 종료되면 같이 종료, recv는 클라이언트가 종료하면 같이 종료
void acceptClient( network::TcpSocket& serverSock );
void serverSend( );
void serverRecv( network::TcpSocket*& clientSock );

int main( ) {
	WSADATA wsaData;
	if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 ) {
		std::cerr << "Failed to initialize Winsock\n";
		return -1;
	}

	try {
		auto serverSock = network::TcpSocket( );

		// bind
		auto sockAddr = network::SockAddr( INADDR_ANY, PORT );
		serverSock.bind( sockAddr );

		// listen
		serverSock.listen( 2 );

		auto acceptThread = std::thread( acceptClient, std::ref( serverSock ) );
		auto sendThread = std::thread( serverSend );

		static auto lastTp = Clock::now( );

		// update
		while ( true ) {
			if ( GetAsyncKeyState( 'Q' ) & 0x8000 ) {
				serverRun = false;
				break;
			}

			auto tp = Clock::now( );
			auto elapsedTime = std::chrono::duration_cast<Seconds>( tp - lastTp );

			if ( elapsedTime < ( 1_s / 30.f ) ) {
				continue;
			}
			else {
				lastTp = tp;
			}

			// 패킷을 이용해서 게임 상태 update
			/*{
				auto lock = std::lock_guard( packetQueueMtx );
				while ( !logPacketQueue.empty( ) ) {
					auto packet = logPacketQueue.front( );
					logPacketQueue.pop( );

					if ( packet.type == PacketType::LOGIN ) {
						std::cout << "로그인 패킷: " << packet.mv.id << '\n';
					}
				}
			}*/

			LogPacketQueue::getInst( ).dispatch( );
			PacketQueue::getInst( ).dispatch( );
		}

		sendThread.join( );
		for ( auto& thread : recvThreads ) {
			thread.join( );
		}

		serverSock.close( );
		acceptThread.join( );
	}
	catch ( const network::Exception& e ) {
		std::cerr << e.what( ) << '\n';
	}
	catch ( const std::exception& e ) {
		std::cerr << e.what( ) << '\n';
	}
	catch ( ... ) {
		std::cerr << "Unknown exception" << '\n';
	}

	WSACleanup( );
}

void acceptClient( network::TcpSocket& serverSock ) {
	while ( serverRun ) {
		auto clientSock = serverSock.acceptUc( );
		if ( clientSock.invalid( ) ) {
			continue;
		}
		
		// 접속한 클라이언트 정보 출력
		auto ip = network::getCounterpartIp( clientSock );
		std::cout << "[TCP 서버] 클라이언트 접속: IP 주소=" << ip.c_str( )
			<< ", 포트 번호=" << ntohs( clientSock.getPort( ) ) << '\n';

		sockMtx.lock( );
		for ( auto& pClient : clients ) {
			if ( !pClient ) {
				pClient = new network::TcpSocket( std::move( clientSock ) );
				recvThreads.push_back( std::thread( serverRecv, std::ref( pClient ) ) );
				break;
			}
		}
		sockMtx.unlock( );
	}
}

void serverSend( ) {
	static auto lastTp = Clock::now( );

	while ( serverRun ) {
		if ( !SendingStorage::getInst( ).getFlag( ) ) {
			continue;
		}

		auto tp = Clock::now( );
		auto elapsedTime = std::chrono::duration_cast<Seconds>( tp - lastTp );
		lastTp = tp;

		if ( elapsedTime < ( 1_s / 30.f ) ) {
			std::this_thread::sleep_for( ( 1_s / 30.f ) - elapsedTime );
		}

		auto buffer = std::array<char, BUFSIZE>( );
		std::uint16_t bufferSize = 0;
		SendingStorage::getInst( ).flush( buffer.data( ), bufferSize );

		// send ------------------------------------------------------
		sockMtx.lock( );
		for ( auto pClient : clients ) {
			if ( !pClient ) {
				continue;
			}

			pClient->send( &bufferSize, sizeof( bufferSize ) );
			pClient->send( buffer.data( ), bufferSize );
		}
		sockMtx.unlock( );
		//------------------------------------------------------------

		SendingStorage::getInst( ).resetFlag( );
	}
}

void serverRecv( network::TcpSocket*& pClientSock ) {
	bool exit = false;

	auto& clientSock = *pClientSock;

	while ( true ) {
		std::uint16_t bufferSize = 0;
		clientSock.recvUc( reinterpret_cast<char*>( &bufferSize ), sizeof( bufferSize ) );
		if ( clientSock.invalid( ) ) {
			continue;
		}

		auto buffer = std::array<char, BUFSIZE>( );
		clientSock.recvUc( buffer.data( ), bufferSize );
		if ( clientSock.invalid( ) ) {
			continue;
		}

		for ( int readCnt = 0; readCnt < bufferSize / sizeof( Packet ); ++readCnt ) {
			auto packet = Packet{
				.type = PacketType::NONE,
			};
			std::copy( buffer.begin( ) + readCnt * sizeof( Packet )
				, buffer.begin( ) + ( readCnt + 1 ) * sizeof( Packet )
				, reinterpret_cast<char*>( &packet ) );

			auto lock = std::lock_guard( packetQueueMtx );
			if ( packet.type == PacketType::LOGIN ) {
				LogPacketQueue::getInst( ).pushPacket( packet );
			}
			else if ( packet.type == PacketType::LEAVE ) {
				exit = true;
				break;
			}
			else if ( packet.type == PacketType::INPUT ) {
				PacketQueue::getInst( ).pushPacket( packet );
			}
		}

		// 클라이언트 접속 종료 체크해서 반복문 탈출
		if ( exit ) {
			break;
		}
	}

	auto ip = network::getCounterpartIp( clientSock );
	std::cout << "[TCP 서버] 클라이언트 종료: IP 주소=" << ip.c_str( )
		<< ", 포트 번호=" << ntohs( clientSock.getPort( ) ) << '\n';

	auto tmp = pClientSock;
	sockMtx.lock( );
	pClientSock = nullptr;
	sockMtx.unlock( );
	delete tmp;
}