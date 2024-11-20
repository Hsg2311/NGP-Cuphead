#include "OverworldPlayer.hpp"
#include "ResourceHandler.hpp"
#include "Camera.hpp"
#include "InputDeviceHandler.hpp"
#include "Timer.hpp"

#include <ranges>
#include <algorithm>

OverworldPlayer::OverworldPlayer( const std::vector<texInfo>& info ) {
	createAnimator( );

	std::ranges::for_each( info, [this]( const texInfo& elem ) {
		auto tex = ResourceHandler::getInst( ).loadTexture( elem.resKey, std::wstring( L"/texture/idle/overworld/" + elem.fileName ) );
		textures_.push_back( tex );

		getAnimator( )->createAnimation( elem.resKey, tex, Vec2( 0.f, 0.f ),
			elem.sliceSize, Vec2( elem.sliceSize.x, 0.f ), elem.duration, elem.frameCount, elem.offset );
	} );

	getAnimator( )->play( info.front( ).resKey );

	createCollider( );
	getCollider( )->setScale( Vec2{ 100.f, 100.f } );
}

void OverworldPlayer::update( ) {
	auto objPos = getObjPos( );
	auto lu = Vec2( -1.f, 1.f );
	auto ru = Vec2( 1.f, 1.f );
	auto ld = Vec2( -1.f, -1.f );
	auto rd = Vec2( 1.f, -1.f );

	lu.normalize( );
	ru.normalize( );
	ld.normalize( );
	rd.normalize( );

	bool bUp = false;
	bool bDown = false;
	bool bLeft = false;
	bool bRight = false;

	if ( KEY_HOLD( InputData::UP ) ) {
		bUp = true;
	}
	if ( KEY_HOLD( InputData::DOWN ) ) {
		bDown = true;
	}
	if ( KEY_HOLD( InputData::LEFT ) ) {
		bLeft = true;
	}
	if ( KEY_HOLD( InputData::RIGHT ) ) {
		bRight = true;
	}
	if ( KEY_HOLD( InputData::LEFT ) && KEY_HOLD( InputData::UP ) ) {
		bLeft = true;
		bUp = true;
	}
	if ( KEY_HOLD( InputData::RIGHT ) && KEY_HOLD( InputData::UP ) ) {
		bRight = true;
		bUp = true;
	}
	if ( KEY_HOLD( InputData::LEFT ) && KEY_HOLD( InputData::DOWN ) ) {
		bLeft = true;
		bDown = true;
	}
	if ( KEY_HOLD( InputData::RIGHT ) && KEY_HOLD( InputData::DOWN ) ) {
		bRight = true;
		bDown = true;
	}

	if ( bUp && !bDown && !bLeft && !bRight ) {
		getAnimator( )->play( L"Walk_Up" );
		objPos.y -= 300.f * fDT;
	}
	if ( bDown && !bUp && !bLeft && !bRight ) {
		getAnimator( )->play( L"Walk_Down" );
		objPos.y += 300.f * fDT;
	}
	if ( bLeft && !bRight && !bUp && !bDown ) {
		getAnimator( )->play( L"Walk_Left" );
		objPos.x -= 300.f * fDT;
	}
	if ( bRight && !bLeft && !bUp && !bDown ) {
		getAnimator( )->play( L"Walk_Right" );
		objPos.x += 300.f * fDT;
	}
	if ( bLeft && bUp && !bDown && !bRight ) {
		getAnimator( )->play( L"Walk_Left_Up" );
		objPos.x -= 300.f * lu.x * fDT;
		objPos.y -= 300.f * lu.y * fDT;
	}
	if ( bRight && bUp && !bDown && !bLeft ) {
		getAnimator( )->play( L"Walk_Right_Up" );
		objPos.x += 300.f * ru.x * fDT;
		objPos.y -= 300.f * ru.y * fDT;
	}
	if ( bLeft && bDown && !bUp && !bRight ) {
		getAnimator( )->play( L"Walk_Left_Down" );
		objPos.x -= 300.f * ld.x * fDT;
		objPos.y += 300.f * ld.y * fDT;
	}
	if ( bRight && bDown && !bUp && !bLeft ) {
		getAnimator( )->play( L"Walk_Right_Down" );
		objPos.x += 300.f * rd.x * fDT;
		objPos.y += 300.f * rd.y * fDT;
	}

	if ( KEY_AWAY( InputData::UP ) ) {
		getAnimator( )->play( L"Idle_Up" );
	}
	if ( KEY_AWAY( InputData::DOWN ) ) {
		getAnimator( )->play( L"Idle_Down" );
	}
	if ( KEY_AWAY( InputData::LEFT ) ) {
		getAnimator( )->play( L"Idle_Left" );
	}
	if ( KEY_AWAY( InputData::RIGHT ) ) {
		getAnimator( )->play( L"Idle_Right" );
	}
	if ( KEY_AWAY( InputData::LEFT ) && KEY_AWAY( InputData::UP ) ) {
		getAnimator( )->play( L"Idle_Left_Up" );
	}
	if ( KEY_AWAY( InputData::RIGHT ) && KEY_AWAY( InputData::UP ) ) {
		getAnimator( )->play( L"Idle_Right_Up" );
	}
	if ( KEY_AWAY( InputData::LEFT ) && KEY_AWAY( InputData::DOWN ) ) {
		getAnimator( )->play( L"Idle_Left_Down" );
	}
	if ( KEY_AWAY( InputData::RIGHT ) && KEY_AWAY( InputData::DOWN ) ) {
		getAnimator( )->play( L"Idle_Right_Down" );
	}

	setObjPos( objPos );
}

void OverworldPlayer::render( HDC hdc ) {
	componentRender( hdc );
}

void OverworldPlayer::onCollision( Object* other ) {
}

void OverworldPlayer::onCollisionEntry( Object* other ) {
	getCollider( )->addCollisionCount( );
}

void OverworldPlayer::onCollisionExit( Object* other ) {
	getCollider( )->subCollisionCount( );
}
