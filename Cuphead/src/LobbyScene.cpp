#include "LobbyScene.hpp"
#include "Background.hpp"

void LobbyScene::entry( ) {
	auto background = new Background( L"Lobby Background", L"lobby/lobby_background.png" );
	background->setObjName( L"Lobby Background" );
	background->setObjPos( Vec2( 640.f, 360.f ) );
	addObject( GROUP_TYPE::BACKGROUND, background );
}