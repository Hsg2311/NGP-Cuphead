#include "LobbyScene.hpp"
#include "SendingStorage.hpp"
#include "EventHandler.hpp"

inline constexpr const char* ID = "test ID";
inline constexpr const char* PW = "test PW";

void LobbyScene::entry( ) {

}

void LobbyScene::handlePacket( const Packet& packet ) {
	switch ( packet.type ) {
	case PacketType::LOGIN: 
		handleLoginPacket( packet );
		break;

	default: break;
	}
}

void LobbyScene::handleLoginPacket( const Packet& packet ) {
	auto packetToSend = Packet{
		.type = PacketType::LOGIN_RESULT,
		.lr = {
			.result = strcmp( packet.lg.id, ID ) == 0 && strcmp( packet.lg.pw, PW ) == 0
		}
	};

	if ( packetToSend.lr.result == true ) {
		EventHandler::getInst( ).addEvent( Event{
			.eventType = EVENT_TYPE::CHANGE_SCENE,
			.wParam = static_cast<DWORD_PTR>( SCENE_TYPE::WORLD_SCENE )
		} );
	}

	SendingStorage::getInst( ).pushPacket( packetToSend );
}