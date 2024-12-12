#include "LobbyScene.hpp"
#include "Background.hpp"
#include "ClickableUI.hpp"
#include "LogPacketQueue.hpp"

/*
Ŭ��� ������ ��� bool �� �� - cupheadLogin, mugmanLogin
Ŭ��� �ϴ� �ڱ� �ڽ��� Ȯ���ϰ� ��������, �ڱ� �ڽſ� �ش��ϴ� bool�� true��
���� �������� - ������ �˷��� (LoginResult ��Ŷ)

��밡 �����ϸ�, ���� ������ �˷��� (LoginResult ��Ŷ)

�� �� true�� �Ǿ��� �� ���� ��ŸƮ ����

���� ��ŸƮ ��ư�� ������ TryGameStart ��Ŷ ������ ����

GameStart ��Ŷ�� ������ �� ��ȯ



Login ��Ŷ���� ���������� Ȯ��
cupheadLogin, mugmanLogin ���� ��Ŷ �޾��� �� Ȱ��ȭ

TryGameStart ��Ŷ �޾��� �� cupheadLogin, mugmanLogin �� �� true�̸�
GameStart ��Ŷ�� ������ �� ��ȯ

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