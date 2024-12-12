#include "LobbyScene.hpp"
#include "SendingStorage.hpp"
#include "EventHandler.hpp"
#include "protocol.hpp"

inline constexpr const char* ID = "cuphead";
inline constexpr const char* PW = "1122";

inline constexpr const char* ID2 = "mugman";
inline constexpr const char* PW2 = "3344";

void LobbyScene::entry( ) {
	hasCupheadChangedScene_ = false;
	hasMugmanChangedScene_ = false;
}

void LobbyScene::handlePacket( const Packet& packet ) {
	switch ( packet.type ) {
	case PacketType::LOGIN: 
		handleLoginPacket( packet );
		break;

	case PacketType::TRY_GAME_START:
		handleTryGameStartPacket( packet );
		break;

	case PacketType::LEAVE:
		handleLeavePacket( packet );
		break;

	case PacketType::CHANGE_SCENE_ACK:
		handleChangeSceneAckPacket( packet );
		break;

	default: break;
	}
}

void LobbyScene::handleLoginPacket( const Packet& packet ) {
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

void LobbyScene::handleTryGameStartPacket( const Packet& packet ) {
	if ( gCupheadLogin && gMugmanLogin ) {
		SendingStorage::getInst( ).pushPacket( Packet{
			.type = PacketType::CHANGE_SCENE,
			.cs = {
				.scene = SCENE_TYPE::WORLD_SCENE
			}
		} );
	}
}

void LobbyScene::handleLeavePacket( const Packet& packet ) {
	packet.lv.imCuphead ? gCupheadLogin = false : gMugmanLogin = false;

	SendingStorage::getInst( ).pushPacket( Packet{
		.type = PacketType::LOGOUT,
		.lo = {
			.imCuphead = packet.lv.imCuphead
		}
	} );
}

void LobbyScene::handleChangeSceneAckPacket( const Packet& packet ) {
	if ( packet.ca.imCuphead ) {
		hasCupheadChangedScene_ = true;
	}
	else {
		hasMugmanChangedScene_ = true;
	}

	if ( hasCupheadChangedScene_ && hasMugmanChangedScene_ ) {
		EventHandler::getInst( ).addEvent( Event{
			.eventType = EVENT_TYPE::CHANGE_SCENE,
			.wParam = static_cast<DWORD_PTR>( SCENE_TYPE::WORLD_SCENE )
		} );
	}
}