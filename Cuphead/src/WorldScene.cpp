#include "WorldScene.hpp"
#include "Background.hpp"
#include "OverworldPlayer.hpp"
#include "PacketQueue.hpp"
#include "SendingStorage.hpp"

void WorldScene::entry( ) {
	SendingStorage::getInst( ).pushPacket( Packet{
		.type = PacketType::CHANGE_SCENE_ACK,
		.ca = {
			.imCuphead = gImCuphead
		}
	} );

	auto background = new Background( L"World Background", L"overworld/world_map.png" );
	background->setObjName( L"World Main Island" );
	background->setObjPos( Vec2( 640.f, 340.f ) );
	addObject( GROUP_TYPE::BACKGROUND, background );

	auto sweetHome = new BackgroundAnim( L"World Sweet Home", L"overworld/home_sweet_home.png", 0.065f, 3 );
	sweetHome->setObjName( L"World Sweet Home" );
	sweetHome->setObjPos( Vec2( 688.f, 637.f ) );
	addObject( GROUP_TYPE::BACKGROUND_ENTITY, sweetHome );
}

void WorldScene::handlePacket( const Packet& packet ) {
	switch ( packet.type ) {
	case PacketType::REGISTER:
		handleRegisterPacket( packet );
		break;

	case PacketType::LOGIN_RESULT:
		handleLoginResultPacket( packet );
		break;

	case PacketType::DESTROY:
		handleDestroyPacket( packet );
		break;

	case PacketType::LOGOUT:
		handleLogoutPacket( packet );
		break;

	case PacketType::MOVE:
		handleMovePacket( packet );
		break;

	case PacketType::CHANGE_SCENE:
		handleChangeScenePacket( packet );
		break;

	case PacketType::REPLICATION:
		handleReplicationPacket( packet );
		break;

	case PacketType::ANIMATION_RPC:
		handleAnimationRPCPacket( packet );
		break;

	default: break;
	}
}

void WorldScene::handleRegisterPacket( const Packet& packet ) {
	auto info2 = std::vector<texInfo>( );
	info2.push_back( texInfo{
		.resKey = L"Idle_Down",
		.fileName = L"idle_down.png",
		.sliceSize = Vec2( 52.f, 96.f ),
		.duration = 0.11f,
		.frameCount = 5,
		} );
	info2.push_back( texInfo{
		.resKey = L"Idle_Up",
		.fileName = L"idle_up.png",
		.sliceSize = Vec2( 52.f, 82.f ),
		.duration = 0.095f,
		.frameCount = 6
		} );
	info2.push_back( texInfo{
		.resKey = L"Idle_Left",
		.fileName = L"idle_left.png",
		.sliceSize = Vec2( 62.f, 92.f ),
		.duration = 0.11f,
		.frameCount = 5
		} );
	info2.push_back( texInfo{
		.resKey = L"Idle_Right",
		.fileName = L"idle_right.png",
		.sliceSize = Vec2( 62.f, 92.f ),
		.duration = 0.11f,
		.frameCount = 5,
		} );
	info2.push_back( texInfo{
		.resKey = L"Idle_Left_Up",
		.fileName = L"idle_left_up.png",
		.sliceSize = Vec2( 56.f, 84.f ),
		.duration = 0.11f,
		.frameCount = 5,
		} );
	info2.push_back( texInfo{
		.resKey = L"Idle_Right_Up",
		.fileName = L"idle_right_up.png",
		.sliceSize = Vec2( 56.f, 84.f ),
		.duration = 0.11f,
		.frameCount = 5,
		} );
	info2.push_back( texInfo{
		.resKey = L"Idle_Left_Down",
		.fileName = L"idle_left_down.png",
		.sliceSize = Vec2( 60.f, 110.f ),
		.duration = 0.09f,
		.frameCount = 7,
		} );
	info2.push_back( texInfo{
		.resKey = L"Idle_Right_Down",
		.fileName = L"idle_right_down.png",
		.sliceSize = Vec2( 60.f, 110.f ),
		.duration = 0.09f,
		.frameCount = 7,
		} );
	info2.push_back( texInfo{
		.resKey = L"Walk_Up",
		.fileName = L"walk_up.png",
		.sliceSize = Vec2( 103.f, 114.f ),
		.duration = 0.065f,
		.frameCount = 12,
		} );
	info2.push_back( texInfo{
		.resKey = L"Walk_Down",
		.fileName = L"walk_down.png",
		.sliceSize = Vec2( 104.f, 110.f ),
		.duration = 0.065f,
		.frameCount = 13,
		} );
	info2.push_back( texInfo{
		.resKey = L"Walk_Left",
		.fileName = L"walk_left.png",
		.sliceSize = Vec2( 64.f, 90.f ),
		.duration = 0.07f,
		.frameCount = 11,
		} );
	info2.push_back( texInfo{
		.resKey = L"Walk_Right",
		.fileName = L"walk_right.png",
		.sliceSize = Vec2( 103.f, 110.f ),
		.duration = 0.07f,
		.frameCount = 11,
		} );
	info2.push_back( texInfo{
		.resKey = L"Walk_Left_Up",
		.fileName = L"walk_left_up.png",
		.sliceSize = Vec2( 64.f, 94.f ),
		.duration = 0.065f,
		.frameCount = 12,
		} );
	info2.push_back( texInfo{
		.resKey = L"Walk_Right_Up",
		.fileName = L"walk_right_up.png",
		.sliceSize = Vec2( 103.f, 114.f ),
		.duration = 0.065f,
		.frameCount = 12,
		} );
	info2.push_back( texInfo{
		.resKey = L"Walk_Left_Down",
		.fileName = L"walk_left_down.png",
		.sliceSize = Vec2( 62.f, 102.f ),
		.duration = 0.065f,
		.frameCount = 12,
		} );
	info2.push_back( texInfo{
		.resKey = L"Walk_Right_Down",
		.fileName = L"walk_right_down.png",
		.sliceSize = Vec2( 103.f, 110.f ),
		.duration = 0.065f,
		.frameCount = 12,
		} );

	auto player = new OverworldPlayer( info2 );
	player->setObjPos( packet.rg.pos );
	player->setID( packet.rg.id );
	player->setDirection( Direction::S );

	if ( packet.rg.groupType == GROUP_TYPE::CUPHEAD ) {
		if ( gImCuphead ) {
			player->setInputEnabled( true );
			Camera::getInst( ).setTarget( player );
		}
		player->setObjName( L"Cuphead Player" );
		addObject( GROUP_TYPE::CUPHEAD, player );
	}
	else if ( packet.rg.groupType == GROUP_TYPE::MUGMAN ) {
		if ( !gImCuphead ) {
			player->setInputEnabled( true );
			Camera::getInst( ).setTarget( player );
		}
		player->setObjName( L"Mugman Player" );
		addObject( GROUP_TYPE::MUGMAN, player );
	}

	PacketQueue::getInst( ).addObject( player );
}

void WorldScene::handleDestroyPacket( const Packet& packet ) {
	auto obj = PacketQueue::getInst( ).getObject( packet.ds.id );
	obj->setAlive( false );

	PacketQueue::getInst( ).removeObject( obj );
}

void WorldScene::handleMovePacket( const Packet& packet ) {
	auto obj = PacketQueue::getInst( ).getObject( packet.mv.id );
	obj->setObjPos( packet.mv.pos );
	obj->setDirection( packet.mv.dir );
}

void WorldScene::handleLogoutPacket( const Packet& packet ) {
	packet.lo.imCuphead ? gCupheadLogin = false : gMugmanLogin = false;
}

void WorldScene::handleLoginResultPacket( const Packet& packet ) {
	auto who = packet.lr.who;
	if ( who == LoginResultPacket::Type::Cuphead ) {
		gCupheadLogin = true;
		gMugmanLogin = packet.lr.mugmanLogin;
	}
	else if ( who == LoginResultPacket::Type::Mugman ) {
		gMugmanLogin = true;
		gCupheadLogin = packet.lr.cupheadLogin;
	}
}

void WorldScene::handleChangeScenePacket( const Packet& packet ) {
	if ( packet.cs.scene != SCENE_TYPE::WORLD_SCENE ) {
		EventHandler::getInst( ).addEvent( Event{
			.eventType = EVENT_TYPE::CHANGE_SCENE,
			.wParam = static_cast<DWORD_PTR>( packet.cs.scene )
		} );
	}
}

void WorldScene::handleReplicationPacket( const Packet& packet ) {
	if ( PacketQueue::getInst( ).hasId( packet.rp.id ) ) {
		return;
	}

	handleRegisterPacket( packet );
}

void WorldScene::handleAnimationRPCPacket( const Packet& packet )
{
	auto obj = PacketQueue::getInst( ).getObject( packet.ar.id );

	switch ( packet.ar.anim )
	{
	case AnimationRPC::Type::IdleDown:
		obj->getAnimator( )->play( L"Idle_Down" );
		break;

	case AnimationRPC::Type::IdleLeft:
		obj->getAnimator( )->play( L"Idle_Left" );
		break;

	case AnimationRPC::Type::IdleLeftDown:
		obj->getAnimator( )->play( L"Idle_Left_Down" );
		break;

	case AnimationRPC::Type::IdleLeftUp:
		obj->getAnimator( )->play( L"Idle_Left_Up" );
		break;

	case AnimationRPC::Type::IdleRight:
		obj->getAnimator( )->play( L"Idle_Right" );
		break;

	case AnimationRPC::Type::IdleRightDown:
		obj->getAnimator( )->play( L"Idle_Right_Down" );
		break;

	case AnimationRPC::Type::IdleRightUp:
		obj->getAnimator( )->play( L"Idle_Right_Up" );
		break;

	case AnimationRPC::Type::IdleUp:
		obj->getAnimator( )->play( L"Idle_Up" );
		break;

	case AnimationRPC::Type::WalkDown:
		obj->getAnimator( )->play( L"Walk_Down" );
		break;

	case AnimationRPC::Type::WalkLeft:
		obj->getAnimator( )->play( L"Walk_Left" );
		break;

	case AnimationRPC::Type::WalkLeftDown:
		obj->getAnimator( )->play( L"Walk_Left_Down" );
		break;

	case AnimationRPC::Type::WalkLeftUp:
		obj->getAnimator( )->play( L"Walk_Left_Up" );
		break;

	case AnimationRPC::Type::WalkRight:
		obj->getAnimator( )->play( L"Walk_Right" );
		break;

	case AnimationRPC::Type::WalkRightDown:
		obj->getAnimator( )->play( L"Walk_Right_Down" );
		break;

	case AnimationRPC::Type::WalkRightUp:
		obj->getAnimator( )->play( L"Walk_Right_Up" );
		break;

	case AnimationRPC::Type::WalkUp:
		obj->getAnimator( )->play( L"Walk_Up" );
		break;

	default:
		break;
	}
}