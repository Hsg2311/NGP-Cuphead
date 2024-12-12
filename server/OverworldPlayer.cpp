#include "OverworldPlayer.hpp"
#include "Timer.hpp"
#include "protocol.hpp"
#include "SendingStorage.hpp"

#include <ranges>
#include <algorithm>

OverworldPlayer::OverworldPlayer( ) {
	
}

void OverworldPlayer::update( ) {
	
}

void OverworldPlayer::onCollision( Object* other ) {
}

void OverworldPlayer::onCollisionEntry( Object* other ) {
	getCollider( )->addCollisionCount( );
}

void OverworldPlayer::onCollisionExit( Object* other ) {
	getCollider( )->subCollisionCount( );
}
