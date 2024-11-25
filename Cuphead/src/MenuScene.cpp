#include "MenuScene.hpp"
#include "Background.hpp"
#include "Camera.hpp"
#include "ClickableUI.hpp"

void MenuScene::update( ) {
	Scene::update( );
}

void MenuScene::entry( ) {
	auto background = new Background( L"Menu Background", L"menu/menu_background.png" );
	background->setObjName( L"Menu Background" );
	background->setObjPos( Vec2( 640.f, 340.f ) );
	addObject( GROUP_TYPE::BACKGROUND, background );

	std::vector<texInfo> info;
	info.push_back( { L"Play Button", L"menu/game_play.png" } );

	auto playButton = new ClickableUI( info );
	playButton->setObjName( L"Play Button" );
	playButton->setObjPos( Vec2( 640.f, 280.f ) );
	playButton->setObjScale( Vec2( 250.f, 50.f ) );
	addObject( GROUP_TYPE::UI, playButton );

	std::vector<texInfo> info2;
	info2.push_back( { L"Exit Button", L"menu/game_exit.png" } );

	auto exitButton = new ClickableUI( info2 );
	exitButton->setObjName( L"Exit Button" );
	exitButton->setObjPos( Vec2( 640.f, 440.f ) );
	exitButton->setObjScale( Vec2( 250.f, 50.f ) );
	addObject( GROUP_TYPE::UI, exitButton );

	auto pos = Vec2( Core::getInst( ).getResolution( ) ) / 2.f;
	Camera::getInst( ).setLookAt( pos );
}

void MenuScene::exit( ) {
	Scene::destroyObjGroupList( );
}
