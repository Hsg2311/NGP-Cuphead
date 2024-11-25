#include "BlinkingUI.hpp"
#include "Timer.hpp"

void BlinkingUI::render( HDC hdc ) {
	auto imageWidth = currTex_->getWidth( );
	auto imageHeight = currTex_->getHeight( );

	auto xDest = static_cast<int>( getObjPos( ).x - imageWidth / 2.f );
	auto yDest = static_cast<int>( getObjPos( ).y - imageHeight / 2.f );

	if ( bAlpha_ ) {
		accTime_ += fDT;
		if ( accTime_ > 0.5f ) {
			bAlpha_ = false;
			accTime_ = 0.f;
		}

		currTex_->draw( hdc, xDest, yDest, imageWidth, imageHeight,
			0, 0, imageWidth, imageHeight, 255 );
	}
	else {
		accTime_ += fDT;
		if ( accTime_ > 0.5f ) {
			bAlpha_ = true;
			accTime_ = 0.f;
		}

		currTex_->draw( hdc, xDest, yDest, imageWidth, imageHeight,
			0, 0, imageWidth, imageHeight, 0 );
	}
}
