#include "WorldScene.hpp"
#include "OverworldPlayer.hpp"
#include "PacketQueue.hpp"
#include "Timer.hpp"
#include "SendingStorage.hpp"

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

	obj->setObjPos( objPos );

	SendingStorage::getInst( ).pushPacket( Packet{
		.type = PacketType::MOVE,
		.mv = {
			.id = packet.in.id,
			.dir = dir,
			.pos = objPos
		}
	} );
}