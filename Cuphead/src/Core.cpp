#include "Core.hpp"
#include "PathHandler.hpp"
#include "Timer.hpp"
#include "InputDeviceHandler.hpp"
#include "SceneHandler.hpp"
#include "CollisionHandler.hpp"
#include "EventHandler.hpp"
#include "Camera.hpp"
#include "protocol.hpp"
#include "SendingStorage.hpp"
#include "LogPacketQueue.hpp"
#include "PacketQueue.hpp"

#include <ranges>
#include <algorithm>
#include <thread>
#include <chrono>
#include <atomic>

using Clock = std::chrono::high_resolution_clock;
using Seconds = std::chrono::duration<float>;
inline constexpr Seconds operator""_s( unsigned long long _Val ) noexcept {
	return Seconds( static_cast<float>( _Val ) );
}

std::atomic<bool> clientRun = true;
std::atomic<bool> sentLeave = false;

void clientSend( network::TcpSocket& serverSock );
void clientRecv( network::TcpSocket& serverSock );

Core::Core( )
	: hWnd_{ nullptr }
	, resolution_{ }
	, hdc_{ nullptr }
	, hBitmap_{ nullptr }
	, hMemDC_{ nullptr }
	, serverSock_{ network::TcpSocket( SOCKET( INVALID_SOCKET ), false ) }
	, hPen_{ }
	, hBrush_{ } {
	sendThread_ = std::thread( clientSend, std::ref( serverSock_ ) );
	recvThread_ = std::thread( clientRecv, std::ref( serverSock_ ) );
}

Core::~Core( ) {
	ReleaseDC( hWnd_, hdc_ );
	DeleteDC( hMemDC_ );
	DeleteObject( hBitmap_ );

	std::ranges::for_each( hPen_, []( HPEN& pen ) { DeleteObject( pen ); } );
	std::ranges::for_each( hBrush_, []( HBRUSH& brush ) { DeleteObject( brush ); } );

	clientRun = false;

	sendThread_.join( );
	while ( !sentLeave ) {}
	std::this_thread::sleep_for( 200ms );
	serverSock_.close( );
	recvThread_.join( );

	WSACleanup( );
}

int Core::init( HWND hWnd, POINT resolution ) {
	WSADATA wsaData;
	if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 ) {
		return false;
	}

	serverSock_ = network::TcpSocket( );

	auto serverAddr = network::SockAddr( "192.168.219.103"sv, PORT );
	serverSock_.connect( serverAddr );

	hWnd_ = hWnd;
	resolution_ = resolution;

	// 해상도 조정
	RECT rc{ 0, 0, resolution_.x, resolution_.y };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, false );
	SetWindowPos( hWnd_, nullptr, 10, 10, rc.right - rc.left, rc.bottom - rc.top, 0 );

	// 메인 윈도우 DC 생성
	hdc_ = GetDC( hWnd_ );

	// Double buffering 용도의 비트맵과 DC 생성
	hBitmap_ = CreateCompatibleBitmap( hdc_, resolution_.x, resolution_.y );
	hMemDC_ = CreateCompatibleDC( hdc_ );
	HBITMAP defaultBmp = (HBITMAP)SelectObject( hMemDC_, hBitmap_ );
	DeleteObject( defaultBmp );

	createPenBrush( );

	// Handler 초기화
	PathHandler::getInst( ).init( );
	Timer::getInst( ).init( );
	InputDeviceHandler::getInst( ).init( );
	SceneHandler::getInst( ).init( );
	Camera::getInst( ).init( );

	return S_OK;
}

void Core::progress( ) {
	// Handler update
	Timer::getInst( ).update(true);
	InputDeviceHandler::getInst( ).update( );

	static constexpr float contextSwitchTimeEndurance = 15.f / 1000.f;

	if ( Timer::getInst().getFDT() < 1.f / 30.f - contextSwitchTimeEndurance ) {
		std::this_thread::sleep_for( Seconds( 1.f / 30.f - contextSwitchTimeEndurance - Timer::getInst( ).getFDT( )) );
	}

	Timer::getInst( ).update(false);

	LogPacketQueue::getInst( ).dispatch( );
	PacketQueue::getInst( ).dispatch( );
	SceneHandler::getInst( ).update( );
	CollisionHandler::getInst( ).update( );
	Camera::getInst( ).update( );

	// Rendering (Double buffering)
	Rectangle( hMemDC_, -1, -1, resolution_.x + 1, resolution_.y + 1 );
	SceneHandler::getInst( ).render( hMemDC_ );
	BitBlt( hdc_, 0, 0, resolution_.x, resolution_.y, hMemDC_, 0, 0, SRCCOPY );

	Timer::getInst( ).render( );

	// Event 지연 처리
	EventHandler::getInst( ).update( );
}

void Core::createPenBrush( ) {
	hPen_[ static_cast<UINT>( PEN_TYPE::RED ) ] = CreatePen( PS_SOLID, 1, RGB( 255, 0, 0 ) );
	hPen_[ static_cast<UINT>( PEN_TYPE::GREEN ) ] = CreatePen( PS_SOLID, 1, RGB( 0, 255, 0 ) );
	hPen_[ static_cast<UINT>( PEN_TYPE::BLUE ) ] = CreatePen( PS_SOLID, 1, RGB( 0, 0, 255 ) );

	hBrush_[ static_cast<UINT>( BRUSH_TYPE::HOLLOW ) ] = (HBRUSH)GetStockObject( HOLLOW_BRUSH );
}

void Core::sendLoginPacket( const char id[ 16 ], const char pw[ 16 ] ) {
	auto loginPacket = Packet{
		.type = PacketType::LOGIN
	};
	std::copy( id, id + 16, loginPacket.lg.id );
	std::copy( pw, pw + 16, loginPacket.lg.pw );

	SendingStorage::getInst( ).pushPacket( loginPacket );
}

void clientSend( network::TcpSocket& serverSock ) {
	static auto lastTp = Clock::now( );

	while ( clientRun || SendingStorage::getInst( ).getFlag( ) ) {
		if ( !SendingStorage::getInst( ).getFlag( ) ) {
			continue;
		}

		auto tp = Clock::now( );
		auto elapsedTime = std::chrono::duration_cast<Seconds>( tp - lastTp );
		lastTp = tp;

		static constexpr float contextSwitchTimeEndurance = 25.f / 1000.f;

		if ( elapsedTime < Seconds( ( 1.f / 30.f ) - contextSwitchTimeEndurance ) ) {
			std::this_thread::sleep_for( Seconds( ( 1.f / 30.f ) - elapsedTime.count() - contextSwitchTimeEndurance ) );
		}

		auto buffer = std::array<char, BUFSIZE>( );
		std::uint16_t bufferSize = 0;
		SendingStorage::getInst( ).flush( buffer.data( ), bufferSize );

		// send ------------------------------------------------------
		serverSock.sendUc( reinterpret_cast<char*>( &bufferSize ), sizeof( bufferSize ) );
		serverSock.sendUc( buffer.data( ), bufferSize );
		//------------------------------------------------------------
	}

	// leave packet 전송
	// queue에 패킷이 남아있는 것은 무시
	auto leavePacket = Packet{
		.type = PacketType::LEAVE,
		.lv = {
			.imCuphead = gImCuphead
		}
	};
	auto packetSize = static_cast<std::uint16_t>( sizeof( Packet ) );
	serverSock.sendUc( reinterpret_cast<char*>( &packetSize ), sizeof( packetSize ) );
	serverSock.sendUc( reinterpret_cast<char*>( &leavePacket ), packetSize );

	sentLeave = true;
}

void clientRecv( network::TcpSocket& serverSock ) {
	while ( clientRun ) {
		std::uint16_t bufferSize = 0;
		serverSock.recvUc( reinterpret_cast<char*>( &bufferSize ), sizeof( bufferSize ) );
		if ( serverSock.invalid( ) ) {
			continue;
		}

		auto buffer = std::array<char, BUFSIZE>( );
		serverSock.recvUc( buffer.data( ), bufferSize );
		if ( serverSock.invalid( ) ) {
			continue;
		}

		for ( int readCnt = 0; readCnt < bufferSize / sizeof( Packet ); ++readCnt ) {
			auto packet = Packet{
				.type = PacketType::NONE,
			};
			std::copy( buffer.begin( ) + readCnt * sizeof( Packet )
				, buffer.begin( ) + ( readCnt + 1 ) * sizeof( Packet )
				, reinterpret_cast<char*>( &packet ) );

			// 패킷 저장
			if ( packet.type == PacketType::LOGIN_RESULT ) {
				LogPacketQueue::getInst( ).pushPacket( packet );
			}
			else {
				PacketQueue::getInst( ).pushPacket( packet );
			}
		}
	}
}