#include "LobbyScene.hpp"
#include "Background.hpp"
#include "ClickableUI.hpp"
#include "LogPacketQueue.hpp"

/*
클라랑 서버에 모두 bool 두 개 - cupheadLogin, mugmanLogin
클라는 일단 자기 자신은 확실하게 들어왔으니, 자기 자신에 해당하는 bool을 true로
내가 누구인지 - 서버가 알려줌 (LoginResult 패킷)

상대가 접속하면, 역시 서버가 알려줌 (LoginResult 패킷)

둘 다 true가 되었을 때 게임 스타트 가능

게임 스타트 버튼을 누르면 TryGameStart 패킷 서버로 보냄

GameStart 패킷을 받으면 씬 전환



Login 패킷으로 누구인지를 확인
cupheadLogin, mugmanLogin 각각 패킷 받았을 때 활성화

TryGameStart 패킷 받았을 때 cupheadLogin, mugmanLogin 둘 다 true이면
GameStart 패킷을 보내고 씬 전환

*/


void LobbyScene::entry( ) {
	auto background = new Background( L"Lobby Background", L"lobby/lobby_background.png" );
	background->setObjName( L"Lobby Background" );
	background->setObjPos( Vec2( 640.f, 360.f ) );
	addObject( GROUP_TYPE::BACKGROUND, background );

	auto readyCuphead = new BackgroundCharacter( L"Ready Cuphead", L"lobby/cuphead.png", true );
	readyCuphead->setObjName( L"Ready Cuphead" );
	readyCuphead->setObjPos( Vec2( 426.f, 300.f ) );
	addObject( GROUP_TYPE::BACKGROUND, readyCuphead );

	auto readyMugman = new BackgroundCharacter( L"Ready Mugman", L"lobby/mugman.png", false );
	readyMugman->setObjName( L"Ready Mugman" );
	readyMugman->setObjPos( Vec2( 854.f, 300.f ) );
	addObject( GROUP_TYPE::BACKGROUND, readyMugman );

	auto info = std::vector<texInfo>( );
	info.push_back( { L"Start Button", L"lobby/start_button.png" } );
	auto startButton = new ClickableUI( info );
	startButton->setObjName( L"Start Button" );
	startButton->setObjPos( Vec2( 640.f, 600.f ) );
	startButton->setObjScale( Vec2( 300.f, 70.f ) );
	addObject( GROUP_TYPE::UI, startButton );
}

void LobbyScene::handlePacket( const Packet& packet ) {
	switch ( packet.type ) {
	case PacketType::LOGIN_RESULT:
		handleLoginResultPacket( packet );
		break;

	case PacketType::TRY_GAME_START_RESULT:
		handleTryGameStartResultPacket( packet );
		break;

	default: break;
	}
}

void LobbyScene::handleLoginResultPacket( const Packet& packet ) {
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

void LobbyScene::handleTryGameStartResultPacket( const Packet& packet ) {
	if ( packet.tg.result ) {
		EventHandler::getInst( ).addEvent( Event{
			.eventType = EVENT_TYPE::CHANGE_SCENE,
			.wParam = static_cast<DWORD_PTR>( SCENE_TYPE::WORLD_SCENE )
		} );
	}
}