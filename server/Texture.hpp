#ifndef __TEXTURE_HPP
#define __TEXTURE_HPP

#include "Res.hpp"
#include "struct.hpp"

#include <atlimage.h>
#include <string>
#include "WinUT.hpp"

class Texture : public Res {
private:
	Texture( ) : texImage_{ } {};
	virtual ~Texture( ) {}

public:
	void load( const std::wstring& filePath ) { texImage_.Load( filePath.c_str( ) ); }
	void draw( HDC hdc, const Vec2& objPos ) { 
		texImage_.Draw( hdc, 
			static_cast<int>( objPos.x - texImage_.GetWidth( ) / 2.f ), 
			static_cast<int>( objPos.y - texImage_.GetHeight( ) / 2.f ), 
			texImage_.GetWidth( ), texImage_.GetHeight( ) );
	}

	void draw( HDC hdc, int xDest, int yDest, int nDestWidth, int nDestHeight,
				int xSrc, int ySrc, int nSrcWidth, int nSrcHeight ) {
		texImage_.Draw( hdc, xDest, yDest, nDestWidth, nDestHeight,
						xSrc, ySrc, nSrcWidth, nSrcHeight );
	}

	void draw( HDC hdc, int xDest, int yDest, int nDestWidth, int nDestHeight,
				int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, BYTE alpha ) {
		texImage_.AlphaBlend( hdc, xDest, yDest, nDestWidth, nDestHeight,
							xSrc, ySrc, nSrcWidth, nSrcHeight, alpha );
	}

	int getWidth( ) const { return texImage_.GetWidth( ); }
	int getHeight( ) const { return texImage_.GetHeight( ); }
	COLORREF getPixel( int x, int y ) const {
		return texImage_.GetPixel( x, y );
	}

private:
	CImage texImage_;

	friend class ResourceHandler;
};

#endif // __TEXTURE_HPP