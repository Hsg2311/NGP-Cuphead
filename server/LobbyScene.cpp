#include "LobbyScene.hpp"
#include "SendingStorage.hpp"
#include "EventHandler.hpp"
#include "protocol.hpp"

inline constexpr const char* ID = "cuphead";
inline constexpr const char* PW = "1122";

inline constexpr const char* ID2 = "mugman";
inline constexpr const char* PW2 = "3344";

void LobbyScene::entry( ) {

}

void LobbyScene::handlePacket( const Packet& packet ) {
	switch ( packet.type ) {
	case PacketType::LOGIN: 
		handleLoginPacket( packet );
		break;

	case PacketType::TRY_GAME_START:
		handleTryGameStartPacket( packet );
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
	auto packetToSend = Packet{
		.type = PacketType::TRY_GAME_START_RESULT,
		.tg = {
			.result = gCupheadLogin && gMugmanLogin
		}
	};

	SendingStorage::getInst( ).pushPacket( packetToSend );

	if ( gCupheadLogin && gMugmanLogin ) {
		EventHandler::getInst( ).addEvent( Event{
			.eventType = EVENT_TYPE::CHANGE_SCENE, 
			.wParam = static_cast<DWORD_PTR>( SCENE_TYPE::WORLD_SCENE )
		} );
	}
}