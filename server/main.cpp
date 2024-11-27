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

// accept�� send�� ������ ����Ǹ� ���� ����, recv�� Ŭ���̾�Ʈ�� �����ϸ� ���� ����
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

		// ������ Ŭ���̾�Ʈ ���� ���
		auto addr = std::array<char, INET_ADDRSTRLEN>( );
		inet_ntop( AF_INET, &clientSock.getAddr( ), addr.data( ), addr.size( ) );
		std::cout << "[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=" << addr.data( )
			<< ", ��Ʈ ��ȣ=" << ntohs( clientSock.getPort( ) ) << '\n';

		// ���� id pool�� ����������.
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
		

		// Ŭ���̾�Ʈ ���� ���� üũ�ؼ� �ݺ��� Ż��
	}

	auto addr = std::array<char, INET_ADDRSTRLEN>( );
	inet_ntop( AF_INET, &clientSock.getAddr( ), addr.data( ), addr.size( ) );
	std::cout << "[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=" << addr.data( )
		<< ", ��Ʈ ��ȣ=" << ntohs( clientSock.getPort( ) ) << '\n';
}
