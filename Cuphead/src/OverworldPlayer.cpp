#include "OverworldPlayer.hpp"
#include "ResourceHandler.hpp"
#include "Camera.hpp"
#include "InputDeviceHandler.hpp"
#include "Timer.hpp"
#include "protocol.hpp"
#include "SendingStorage.hpp"

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

	auto packet = Packet{
		.type = PacketType::INPUT,
		.in = {
			.id = getNetworkId( ),
			.left = bLeft,
			.right = bRight,
			.up = bUp,
			.down = bDown,
		}
	};

	if ( bUp || bDown || bRight || bLeft ) {
		SendingStorage::getInst( ).pushPacket( packet );
	}
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
