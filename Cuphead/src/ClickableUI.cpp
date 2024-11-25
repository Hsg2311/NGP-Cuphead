#include "ClickableUI.hpp"
#include "InputDeviceHandler.hpp"
#include "EventHandler.hpp"

void ClickableUI::update( ) {
	auto bLbtnTap = KEY_TAP( InputData::MOUSE_LBTN );
	auto bLbtnAway = KEY_AWAY( InputData::MOUSE_LBTN );

	if ( mouseOnCheck( ) ) {
		//mouseOn( );

		if ( bLbtnTap ) {
			//mouseLbtnDown( );
			bLbtnDown_ = true;
		}
		else if ( bLbtnAway ) {
			//mouseLbtnUp( );

			if ( bLbtnDown_ ) {
				mouseLbtnClicked( );
			}
			bLbtnDown_ = false;
		}
	}
	else {
		if ( bLbtnAway ) {
			bLbtnDown_ = false;
		}
	}
}

void ClickableUI::render( HDC hdc ) {
	auto imageWidth = currTex_->getWidth( );
	auto imageHeight = currTex_->getHeight( );

	auto xDest = static_cast<int>( getObjPos( ).x - imageWidth / 2.f );
	auto yDest = static_cast<int>( getObjPos( ).y - imageHeight / 2.f );

	if ( bMouseOn_ ) {
		currTex_->draw( hdc, xDest, yDest, imageWidth, imageHeight,
			0, 0, imageWidth, imageHeight, 255 );
	}
	else {
		currTex_->draw( hdc, xDest, yDest, imageWidth, imageHeight,
			0, 0, imageWidth, imageHeight, 100 );
	}
	
	componentRender( hdc );
}

bool ClickableUI::mouseOnCheck( ) {
	auto mousePos = MOUSE_POS;
	auto objPos = getObjPos( );
	auto objScale = getObjScale( );
	
	if ( mousePos.x >= objPos.x - objScale.x / 2.f && mousePos.x <= objPos.x + objScale.x / 2.f
		&& mousePos.y >= objPos.y - objScale.y / 2.f && mousePos.y <= objPos.y + objScale.y / 2.f ) {
		bMouseOn_ = true;
		return true;
	}
	else {
		bMouseOn_ = false;
		return false;
	}
}

void ClickableUI::mouseOn( ) {
}

void ClickableUI::mouseLbtnDown( ) {
}

void ClickableUI::mouseLbtnUp( ) {
}

void ClickableUI::mouseLbtnClicked( ) {
	if ( getObjName( ) == L"Play Button" ) {
		EventHandler::getInst( ).addEvent( Event {
			.eventType = EVENT_TYPE::CHANGE_SCENE,
			.wParam = static_cast<DWORD_PTR>( SCENE_TYPE::WORLD_SCENE )
		} );
	}
	else if ( getObjName( ) == L"Exit Button" ) {
		PostQuitMessage( 0 );
	}
}
