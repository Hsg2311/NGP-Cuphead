#include "Core.hpp"
#include "PathHandler.hpp"
#include "Timer.hpp"
#include "InputDeviceHandler.hpp"
#include "SceneHandler.hpp"
#include "CollisionHandler.hpp"
#include "EventHandler.hpp"
#include <ranges>
#include <algorithm>

Core::Core( )
	: hWnd_{ nullptr }
	, resolution_{ }
	, hdc_{ nullptr }
	, hBitmap_{ nullptr }
	, hMemDC_{ nullptr }
	, hPen_{ }
	, hBrush_{ }
{}

Core::~Core( ) {
	ReleaseDC( hWnd_, hdc_ );
	DeleteDC( hMemDC_ );
	DeleteObject( hBitmap_ );

	std::ranges::for_each( hPen_, []( HPEN& pen ) { DeleteObject( pen ); } );
	std::ranges::for_each( hBrush_, []( HBRUSH& brush ) { DeleteObject( brush ); } );
}

int Core::init( HWND hWnd, POINT resolution ) {
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

	CreatePenBrush( );

	// Handler 초기화
	PathHandler::GetInst( ).init( );
	Timer::GetInst( ).init( );
	InputDeviceHandler::GetInst( ).init( );
	SceneHandler::GetInst( ).init( );

	return S_OK;
}

void Core::progress( ) {
	// Handler update
	Timer::GetInst( ).update( );
	InputDeviceHandler::GetInst( ).update( );

	SceneHandler::GetInst( ).update( );
	CollisionHandler::GetInst( ).update( );

	// Rendering (Double buffering)
	Rectangle( hMemDC_, -1, -1, resolution_.x + 1, resolution_.y + 1 );
	SceneHandler::GetInst( ).render( hMemDC_ );
	BitBlt( hdc_, 0, 0, resolution_.x, resolution_.y, hMemDC_, 0, 0, SRCCOPY );

	Timer::GetInst( ).render( );

	// Event 지연 처리
	EventHandler::GetInst( ).update( );
}

void Core::CreatePenBrush( ) {
	hPen_[ static_cast<UINT>( PEN_TYPE::RED ) ] = CreatePen( PS_SOLID, 1, RGB( 255, 0, 0 ) );
	hPen_[ static_cast<UINT>( PEN_TYPE::GREEN ) ] = CreatePen( PS_SOLID, 1, RGB( 0, 255, 0 ) );
	hPen_[ static_cast<UINT>( PEN_TYPE::BLUE ) ] = CreatePen( PS_SOLID, 1, RGB( 0, 0, 255 ) );

	hBrush_[ static_cast<UINT>( BRUSH_TYPE::HOLLOW ) ] = (HBRUSH)GetStockObject( HOLLOW_BRUSH );
}
