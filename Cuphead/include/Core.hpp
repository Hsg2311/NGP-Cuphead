#ifndef __CORE_HPP
#define __CORE_HPP

#include "define.hpp"
#include <array>
#include <Windows.h>

class Core {
	SINGLETON( Core );

public:
	int init( HWND hWnd, POINT resolution );
	void progress( );
	void CreatePenBrush( );

	HWND getHwnd( ) const { return hWnd_; }
	POINT getResolution( ) const { return resolution_; }
	HPEN getPen( PEN_TYPE type ) const { return hPen_[ static_cast<UINT>( type ) ]; }
	HBRUSH getBrush( BRUSH_TYPE type ) const { return hBrush_[ static_cast<UINT>( type ) ]; }

private:
	HWND hWnd_;
	POINT resolution_;
	HDC hdc_;

	HBITMAP hBitmap_;
	HDC hMemDC_;

	std::array<HPEN, static_cast<UINT>( PEN_TYPE::EOE )> hPen_;
	std::array<HBRUSH, static_cast<UINT>( BRUSH_TYPE::EOE )> hBrush_;
};

#endif // __CORE_HPP