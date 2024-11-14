#ifndef __SELECT_GDI_OBJECT_HPP
#define __SELECT_GDI_OBJECT_HPP

#include "Core.hpp"
#include <Windows.h>

class SelectGdiObject {
public:
	SelectGdiObject( HDC hdc, PEN_TYPE pen, BRUSH_TYPE brush ) 
		: hdc_{ hdc }
		, hDefaultPen_{ static_cast<HPEN>( SelectObject( hdc_, Core::GetInst( ).getPen( pen ) ) ) }
		, hDefaultBrush_{ static_cast<HBRUSH>( SelectObject( hdc_, Core::GetInst( ).getBrush( brush ) ) ) } 
	{}

	~SelectGdiObject( ) {
		SelectObject( hdc_, hDefaultPen_ );
		SelectObject( hdc_, hDefaultBrush_ );
	}

private:
	HDC hdc_;
	HPEN hDefaultPen_;
	HBRUSH hDefaultBrush_;
};

#endif // __SELECT_GDI_OBJECT_HPP