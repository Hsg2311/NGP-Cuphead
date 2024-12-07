#include "SceneHandler.hpp"
#include "MenuScene.hpp"
#include "TitleScene.hpp"
#include "WorldScene.hpp"

#include "BossScene.hpp"

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
	// Scene ����
	sceneList_[ static_cast<UINT>( SCENE_TYPE::TITLE_SCENE ) ] = new TitleScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::TITLE_SCENE ) ]->setSceneName( L"Title Scene" );

	sceneList_[ static_cast<UINT>( SCENE_TYPE::MENU_SCENE ) ] = new MenuScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::MENU_SCENE ) ]->setSceneName( L"Menu Scene" );

	sceneList_[ static_cast<UINT>( SCENE_TYPE::WORLD_SCENE ) ] = new WorldScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::WORLD_SCENE ) ]->setSceneName( L"World Scene" );

	sceneList_[static_cast<UINT>(SCENE_TYPE::BOSS_SCENE)] = new BossScene();
	sceneList_[static_cast<UINT>(SCENE_TYPE::BOSS_SCENE)]->setSceneName(L"Boss Scene");
	// ���� Scene ����
	currScene_ = sceneList_[ static_cast<UINT>( SCENE_TYPE::BOSS_SCENE) ];
	currSceneType_ = SCENE_TYPE::BOSS_SCENE;
	currScene_->entry( );
}
