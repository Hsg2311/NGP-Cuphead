#include "SceneHandler.hpp"
#include "LobbyScene.hpp"
#include "WorldScene.hpp"

#include "SlimeBossScene.hpp"

SceneHandler::SceneHandler( )
	: sceneList_{ }
	, currScene_{ nullptr }
	, currSceneType_{ SCENE_TYPE::LOBBY_SCENE } {}

SceneHandler::~SceneHandler( ) {
	for ( auto& scene : sceneList_ ) {
		delete scene;
	}
}

void SceneHandler::init( ) {
	sceneList_[ static_cast<UINT>( SCENE_TYPE::LOBBY_SCENE ) ] = new LobbyScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::LOBBY_SCENE ) ]->setSceneName( L"Lobby Scene" );

	sceneList_[ static_cast<UINT>( SCENE_TYPE::WORLD_SCENE ) ] = new WorldScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::WORLD_SCENE ) ]->setSceneName( L"World Scene" );

	sceneList_[static_cast<UINT>(SCENE_TYPE::SlIME_SCENE)] = new SlimeBossScene();
	sceneList_[static_cast<UINT>(SCENE_TYPE::SlIME_SCENE)]->setSceneName(L"Boss Scene");

	// 현재 Scene 설정
	currScene_ = sceneList_[ static_cast<UINT>( SCENE_TYPE::LOBBY_SCENE) ];
	currSceneType_ = SCENE_TYPE::LOBBY_SCENE;
	currScene_->entry( );
}
