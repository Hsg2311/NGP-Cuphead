#include "Network.hpp"
#include "protocol.hpp"

#include <iostream>
#include <thread>
#include <array>
#include <vector>
#include <atomic>
#include <ranges>
#include <algorithm>

std::vector<network::TcpSocket> clients;
std::vector<std::thread> recvThreads;

std::atomic<bool> serverRun = true;

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
		auto serverThread = std::thread( serverSend );

		// update
		// ...
		while ( true ) {


			if ( GetAsyncKeyState( 'Q' ) & 0x8000 ) {
				serverRun = false;
				break;
			}
		}

		serverThread.join( );
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
		auto addr = std::array<char, INET_ADDRSTRLEN>( );
		inet_ntop( AF_INET, &clientSock.getAddr( ), addr.data( ), addr.size( ) );
		std::cout << "[TCP 서버] 클라이언트 접속: IP 주소=" << addr.data( )
			<< ", 포트 번호=" << ntohs( clientSock.getPort( ) ) << '\n';

		// 차라리 id pool을 만들어버리자.
		clients.push_back( std::move( clientSock ) );

		recvThreads.push_back( std::thread( serverRecv, std::ref( clientSock ) ) );
	}
}

void serverSend( ) {
	while ( serverRun ) {

	}
}

void serverRecv( network::TcpSocket& clientSock ) {
	while ( true ) {
		

		// 클라이언트 접속 종료 체크해서 반복문 탈출
	}

	auto addr = std::array<char, INET_ADDRSTRLEN>( );
	inet_ntop( AF_INET, &clientSock.getAddr( ), addr.data( ), addr.size( ) );
	std::cout << "[TCP 서버] 클라이언트 종료: IP 주소=" << addr.data( )
		<< ", 포트 번호=" << ntohs( clientSock.getPort( ) ) << '\n';
}
