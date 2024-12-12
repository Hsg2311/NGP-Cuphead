#include "SceneHandler.hpp"
#include "MenuScene.hpp"
#include "TitleScene.hpp"
#include "LobbyScene.hpp"
#include "WorldScene.hpp"

#include "SlimeScene.hpp"

SceneHandler::SceneHandler( )
	: sceneList_{ }
	, currScene_{ nullptr }
	, currSceneType_{ SCENE_TYPE::TITLE_SCENE }
{}

SceneHandler::~SceneHandler( ) {
	for ( auto& scene : sceneList_ ) {
		delete scene;
	}
}

void SceneHandler::init( ) {
	// Scene 생성
	sceneList_[ static_cast<UINT>( SCENE_TYPE::TITLE_SCENE ) ] = new TitleScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::TITLE_SCENE ) ]->setSceneName( L"Title Scene" );

	sceneList_[ static_cast<UINT>( SCENE_TYPE::MENU_SCENE ) ] = new MenuScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::MENU_SCENE ) ]->setSceneName( L"Menu Scene" );

	sceneList_[ static_cast<UINT>( SCENE_TYPE::LOBBY_SCENE ) ] = new LobbyScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::LOBBY_SCENE ) ]->setSceneName( L"Lobby Scene" );

	sceneList_[ static_cast<UINT>( SCENE_TYPE::WORLD_SCENE ) ] = new WorldScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::WORLD_SCENE ) ]->setSceneName( L"World Scene" );

	sceneList_[static_cast<UINT>(SCENE_TYPE::SlIME_SCENE)] = new SlimeScene();
	sceneList_[static_cast<UINT>(SCENE_TYPE::SlIME_SCENE)]->setSceneName(L"Slime Scene");

	// 현재 Scene 설정
	currScene_ = sceneList_[ static_cast<UINT>( SCENE_TYPE::SlIME_SCENE) ];
	currSceneType_ = SCENE_TYPE::SlIME_SCENE;
	currScene_->entry( );
}
