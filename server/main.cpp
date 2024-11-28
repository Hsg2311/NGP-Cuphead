#include "Network.hpp"
#include "protocol.hpp"
#include "SendingStorage.hpp"

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

std::vector<network::TcpSocket> clients;
std::vector<std::thread> recvThreads;

std::atomic<bool> serverRun = true;

std::queue<Packet> packetQueue;
std::queue<Packet> logPacketQueue;

// accept랑 send는 서버가 종료되면 같이 종료, recv는 클라이언트가 종료하면 같이 종료
void acceptClient( network::TcpSocket& serverSock );
void serverSend( );
void serverRecv( network::TcpSocket& clientSock );

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

		// update
		// ...
		while ( true ) {
			if ( GetAsyncKeyState( 'Q' ) & 0x8000 ) {
				serverRun = false;
				break;
			}
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

		clients.push_back( std::move( clientSock ) );

		recvThreads.push_back( std::thread( serverRecv, std::ref( clients.back( ) ) ) );
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
		SendingStorage::getInst( ).copyTo( buffer.data( ), bufferSize );

		// send ------------------------------------------------------
		for ( auto& client : clients ) {
			client.send( &bufferSize, sizeof( bufferSize ) );
			client.send( buffer.data( ), bufferSize );
		}
		//------------------------------------------------------------

		SendingStorage::getInst( ).resetFlag( );
	}
}

void serverRecv( network::TcpSocket& clientSock ) {
	while ( true ) {
		std::uint16_t bufferSize = 0;
		clientSock.recv( reinterpret_cast<char*>( &bufferSize ), sizeof( bufferSize ) );

		auto buffer = std::array<char, BUFSIZE>( );
		clientSock.recv( buffer.data( ), bufferSize );

		// recv ------------------------------------------------------
		for ( int readCnt = 0; readCnt < bufferSize / sizeof( Packet ); ++readCnt ) {
			Packet packet;
			std::copy( buffer.begin( ) + readCnt * sizeof( Packet )
				, buffer.begin( ) + ( readCnt + 1 ) * sizeof( Packet )
				, reinterpret_cast<char*>( &packet ) );

			packetQueue.push( packet );
		}

		// 클라이언트 접속 종료 체크해서 반복문 탈출
	}

	auto ip = network::getCounterpartIp( clientSock );
	std::cout << "[TCP 서버] 클라이언트 종료: IP 주소=" << ip.c_str( )
		<< ", 포트 번호=" << ntohs( clientSock.getPort( ) ) << '\n';
}