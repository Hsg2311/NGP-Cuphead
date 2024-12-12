#include "WorldScene.hpp"
#include "OverworldPlayer.hpp"
#include "PacketQueue.hpp"
#include "Timer.hpp"
#include "SendingStorage.hpp"

inline constexpr const char* ID = "cuphead";
inline constexpr const char* PW = "1122";

inline constexpr const char* ID2 = "mugman";
inline constexpr const char* PW2 = "3344";

void WorldScene::entry( ) {
	auto cuphead = new OverworldPlayer( );

	if ( cuphead->getID( ).has_value( ) ) {
		cuphead->setObjName( L"Cuphead Player" );
		cuphead->setObjPos( Vec2( 800.f, 780.f ) );
		addObject( GROUP_TYPE::CUPHEAD, cuphead );

		PacketQueue::getInst( ).addObject( cuphead );

		SendingStorage::getInst( ).pushPacket( Packet{
			.type = PacketType::REGISTER,
			.rg = {
				.id = cuphead->getID( ).value( ),
				.groupType = GROUP_TYPE::CUPHEAD,
				.pos = cuphead->getObjPos( )
			}
		} );
	}
	else {
		// Error: Failed to allocate network ID
		delete cuphead;
	}

	auto mugman = new OverworldPlayer( );

	if ( mugman->getID( ).has_value( ) ) {
		mugman->setObjName( L"Mugman Player" );
		mugman->setObjPos( Vec2( 800.f, 780.f ) );
		addObject( GROUP_TYPE::MUGMAN, mugman );

		PacketQueue::getInst( ).addObject( mugman );

		SendingStorage::getInst( ).pushPacket( Packet{
			.type = PacketType::REGISTER,
			.rg = {
				.id = mugman->getID( ).value( ),
				.groupType = GROUP_TYPE::MUGMAN,
				.pos = mugman->getObjPos( )
			}
			} );
	}
	else {
		// Error: Failed to allocate network ID
		delete mugman;
	}
}

void WorldScene::handlePacket( const Packet& packet ) {
	switch ( packet.type ) {
	case PacketType::INPUT:
		handleInputPacket( packet );
		break;

	case PacketType::LEAVE:
		handleLeavePacket( packet );
		break;

	case PacketType::LOGIN:
		handleLoginPacket( packet );
		break;

	case PacketType::TRY_GAME_START:
		handleTryGameStartPacket( packet );
		break;

	case PacketType::CHANGE_SCENE_ACK:
		handleChangeSceneAckPacket( packet );
		break;

	default: break;
	}
}

void WorldScene::handleInputPacket( const Packet& packet ) {
	auto obj = PacketQueue::getInst( ).getObject( packet.in.id );
	auto objPos = obj->getObjPos( );

	auto lu = Vec2( -1.f, 1.f );
	auto ru = Vec2( 1.f, 1.f );
	auto ld = Vec2( -1.f, -1.f );
	auto rd = Vec2( 1.f, -1.f );

	lu.normalize( );
	ru.normalize( );
	ld.normalize( );
	rd.normalize( );

	bool bUp = packet.in.up;
	bool bDown = packet.in.down;
	bool bLeft = packet.in.left;
	bool bRight = packet.in.right;

	Direction dir = Direction::NONE;

	if ( bUp && !bDown && !bLeft && !bRight ) {
		objPos.y -= 300.f * Timer::getInst( ).getFDT( );
		dir = Direction::N;
	}
	if ( bDown && !bUp && !bLeft && !bRight ) {
		objPos.y += 300.f * Timer::getInst( ).getFDT( );
		dir = Direction::S;
	}
	if ( bLeft && !bRight && !bUp && !bDown ) {
		objPos.x -= 300.f * Timer::getInst( ).getFDT( );
		dir = Direction::W;
	}
	if ( bRight && !bLeft && !bUp && !bDown ) {
		objPos.x += 300.f * Timer::getInst( ).getFDT( );
		dir = Direction::E;
	}
	if ( bLeft && bUp && !bDown && !bRight ) {
		objPos.x -= 300.f * lu.x * Timer::getInst( ).getFDT( );
		objPos.y -= 300.f * lu.y * Timer::getInst( ).getFDT( );
		dir = Direction::NW;
	}
	if ( bRight && bUp && !bDown && !bLeft ) {
		objPos.x += 300.f * ru.x * Timer::getInst( ).getFDT( );
		objPos.y -= 300.f * ru.y * Timer::getInst( ).getFDT( );
		dir = Direction::NE;
	}
	if ( bLeft && bDown && !bUp && !bRight ) {
		objPos.x -= 300.f * ld.x * Timer::getInst( ).getFDT( );
		objPos.y += 300.f * ld.y * Timer::getInst( ).getFDT( );
		dir = Direction::SW;
	}
	if ( bRight && bDown && !bUp && !bLeft ) {
		objPos.x += 300.f * rd.x * Timer::getInst( ).getFDT( );
		objPos.y += 300.f * rd.y * Timer::getInst( ).getFDT( );
		dir = Direction::SE;
	}

	if ( auto player = dynamic_cast<OverworldPlayer*>( obj ) ) {
		// offset: (1160.f, 815.f)
		const auto pixel = tex_->getPixel( 
			std::clamp( static_cast<int>( objPos.x ) - 1160 + 640, 0, tex_->getWidth( ) - 1 ),
			std::clamp( static_cast<int>( objPos.y ) + player->getImageHeight( ) / 2 - 815 + 340, 0, tex_->getHeight( ) - 1 )
		);
		
		const auto WorldCollisionColor = RGB( 255, 0, 0 );
		const auto slimeStageCollisionColor = RGB( 0, 255, 0 );
		const auto sunflowerStageCollisionColor = RGB( 0, 0, 255 );

		if ( pixel == WorldCollisionColor ) {
			return;
		}
	}

	obj->setObjPos( objPos );

	SendingStorage::getInst( ).pushPacket( Packet{
		.type = PacketType::MOVE,
		.mv = {
			.id = packet.in.id,
			.dir = ( dir == Direction::NONE ) ? packet.in.dir : dir,
			.pos = objPos
		}
	} );

	// Animation RPC
	auto animRPCPacket = Packet{
		.type = PacketType::ANIMATION_RPC,
		.ar = {
			.id = packet.in.id,
		}
	};

	switch ( dir ) {
	case Direction::NONE:
		switch ( packet.in.dir ) {
		case Direction::E: animRPCPacket.ar.anim = AnimationRPC::Type::IdleRight; break;
		case Direction::W: animRPCPacket.ar.anim = AnimationRPC::Type::IdleLeft; break;
		case Direction::S: animRPCPacket.ar.anim = AnimationRPC::Type::IdleDown; break;
		case Direction::N: animRPCPacket.ar.anim = AnimationRPC::Type::IdleUp; break;
		case Direction::NE: animRPCPacket.ar.anim = AnimationRPC::Type::IdleRightUp; break;
		case Direction::NW: animRPCPacket.ar.anim = AnimationRPC::Type::IdleLeftUp; break;
		case Direction::SE: animRPCPacket.ar.anim = AnimationRPC::Type::IdleRightDown; break;
		case Direction::SW: animRPCPacket.ar.anim = AnimationRPC::Type::IdleLeftDown; break;
		default: std::terminate( ); break;
		}
		break;

	case Direction::E: animRPCPacket.ar.anim = AnimationRPC::Type::WalkRight; break;
	case Direction::W: animRPCPacket.ar.anim = AnimationRPC::Type::WalkLeft; break;
	case Direction::S: animRPCPacket.ar.anim = AnimationRPC::Type::WalkDown; break;
	case Direction::N: animRPCPacket.ar.anim = AnimationRPC::Type::WalkUp; break;
	case Direction::NE: animRPCPacket.ar.anim = AnimationRPC::Type::WalkRightUp; break;
	case Direction::NW: animRPCPacket.ar.anim = AnimationRPC::Type::WalkLeftUp; break;
	case Direction::SE: animRPCPacket.ar.anim = AnimationRPC::Type::WalkRightDown; break;
	case Direction::SW: animRPCPacket.ar.anim = AnimationRPC::Type::WalkLeftDown; break;
	default: std::terminate( ); break;
	}

	SendingStorage::getInst( ).pushPacket( animRPCPacket );
}

void WorldScene::handleTryGameStartPacket( const Packet& packet ) {
	if ( gCupheadLogin && gMugmanLogin ) {
		SendingStorage::getInst( ).pushPacket( Packet{
			.type = PacketType::CHANGE_SCENE,
			.cs = {
				.scene = SCENE_TYPE::WORLD_SCENE
			}
		} );
	}
}

void WorldScene::handleLeavePacket( const Packet& packet ) {
	if ( packet.lv.imCuphead ) {
		gCupheadLogin = false;

		for ( auto obj : getGroup( GROUP_TYPE::CUPHEAD ) ) {
			if ( obj->isAlive( ) ) {
				obj->setAlive( false );
				SendingStorage::getInst( ).pushPacket( Packet{
					.type = PacketType::DESTROY,
					.ds = {
						.id = obj->getID( ).value( )
					}
				} );

				PacketQueue::getInst( ).removeObject( obj );
			}
		}
	}
	else {
		gMugmanLogin = false;

		for ( auto obj : getGroup( GROUP_TYPE::MUGMAN ) ) {
			if ( obj->isAlive( ) ) {
				obj->setAlive( false );
				SendingStorage::getInst( ).pushPacket( Packet{
					.type = PacketType::DESTROY,
					.ds = {
						.id = obj->getID( ).value( )
					}
					} );

				PacketQueue::getInst( ).removeObject( obj );
			}
		}
	}
	
	if ( !gCupheadLogin && !gMugmanLogin ) {
		EventHandler::getInst( ).addEvent( Event{
			.eventType = EVENT_TYPE::CHANGE_SCENE,
			.wParam = static_cast<DWORD_PTR>( SCENE_TYPE::LOBBY_SCENE )
		} );
	}

	SendingStorage::getInst( ).pushPacket( Packet{
		.type = PacketType::LOGOUT,
		.lo = {
			.imCuphead = packet.lv.imCuphead
		}
	} );
}

void WorldScene::handleLoginPacket( const Packet& packet ) {
	const auto isCuphead = strcmp( packet.lg.id, ID ) == 0 && strcmp( packet.lg.pw, PW ) == 0;
	const auto isMugman = strcmp( packet.lg.id, ID2 ) == 0 && strcmp( packet.lg.pw, PW2 ) == 0;

	auto who = LoginResultPacket::Type::None;
	if ( isCuphead ) {
		who = LoginResultPacket::Type::Cuphead;
		gCupheadLogin = true;
	}
	else if ( isMugman ) {
		who = LoginResultPacket::Type::Mugman;
		gMugmanLogin = true;
	}

	auto packetToSend = Packet{
		.type = PacketType::LOGIN_RESULT,
		.lr = {
			.result = isCuphead || isMugman,
			.cupheadLogin = gCupheadLogin,
			.mugmanLogin = gMugmanLogin,
			.who = who
		}
	};

	SendingStorage::getInst( ).pushPacket( packetToSend );
}

void WorldScene::handleChangeSceneAckPacket( const Packet& packet ) {
	// REPLICATION
	const auto vCuphead = getGroup( GROUP_TYPE::CUPHEAD );
	for ( auto cuphead : vCuphead ) {
		if ( cuphead->isAlive( ) ) {
			SendingStorage::getInst( ).pushPacket( Packet{
				.type = PacketType::REPLICATION,
				.rg = {
					.id = cuphead->getID( ).value( ),
					.groupType = GROUP_TYPE::CUPHEAD,
					.pos = cuphead->getObjPos( )
				}
			} );
		}
	}

	const auto vMugman = getGroup( GROUP_TYPE::MUGMAN );
	for ( auto mugman : vMugman ) {
		if ( mugman->isAlive( ) ) {
			SendingStorage::getInst( ).pushPacket( Packet{
				.type = PacketType::REPLICATION,
				.rg = {
					.id = mugman->getID( ).value( ),
					.groupType = GROUP_TYPE::MUGMAN,
					.pos = mugman->getObjPos( )
				}
			} );
		}
	}

	// REGISTER
	if ( packet.ca.imCuphead ) {
		auto cuphead = new OverworldPlayer( );

		if ( cuphead->getID( ).has_value( ) ) {
			cuphead->setObjName( L"Cuphead Player" );
			cuphead->setObjPos( Vec2( 800.f, 780.f ) );
			addObject( GROUP_TYPE::CUPHEAD, cuphead );

			PacketQueue::getInst( ).addObject( cuphead );

			SendingStorage::getInst( ).pushPacket( Packet{
				.type = PacketType::REGISTER,
				.rg = {
					.id = cuphead->getID( ).value( ),
					.groupType = GROUP_TYPE::CUPHEAD,
					.pos = cuphead->getObjPos( )
				}
				} );
		}
		else {
			// Error: Failed to allocate network ID
			delete cuphead;
		}
	}
	else {
		auto mugman = new OverworldPlayer( );

		if ( mugman->getID( ).has_value( ) ) {
			mugman->setObjName( L"Mugman Player" );
			mugman->setObjPos( Vec2( 800.f, 780.f ) );
			addObject( GROUP_TYPE::MUGMAN, mugman );

			PacketQueue::getInst( ).addObject( mugman );

			SendingStorage::getInst( ).pushPacket( Packet{
				.type = PacketType::REGISTER,
				.rg = {
					.id = mugman->getID( ).value( ),
					.groupType = GROUP_TYPE::MUGMAN,
					.pos = mugman->getObjPos( )
				}
				} );
		}
		else {
			// Error: Failed to allocate network ID
			delete mugman;
		}
	}
}