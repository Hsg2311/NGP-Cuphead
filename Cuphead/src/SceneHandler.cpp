#include "SceneHandler.hpp"
<<<<<<< HEAD
#include "MenuScene.hpp"
#include "TitleScene.hpp"
#include "WorldScene.hpp"
=======
#include "Title_Scene.hpp"
#include "Start_Scene.hpp"
#include "Tool_Scene.hpp"
>>>>>>> 4a7d3951422e1aa00ff62c3f7f8d77d88525af52

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
<<<<<<< HEAD
	sceneList_[ static_cast<UINT>( SCENE_TYPE::TITLE_SCENE ) ] = new TitleScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::TITLE_SCENE ) ]->setSceneName( L"Title Scene" );
=======
	sceneList_[ static_cast<UINT>( SCENE_TYPE::TITLE_SCENE ) ] = new Title_Scene{ };
	sceneList_[ static_cast<UINT>( SCENE_TYPE::TITLE_SCENE) ]->setSceneName( L"Title Scence" );

	sceneList_[static_cast<UINT>(SCENE_TYPE::START_SCENE)] = new Start_Scene{ };
	sceneList_[static_cast<UINT>(SCENE_TYPE::START_SCENE)]->setSceneName(L"Title Scence");

>>>>>>> 4a7d3951422e1aa00ff62c3f7f8d77d88525af52

	sceneList_[ static_cast<UINT>( SCENE_TYPE::MENU_SCENE ) ] = new MenuScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::MENU_SCENE ) ]->setSceneName( L"Menu Scene" );

	sceneList_[ static_cast<UINT>( SCENE_TYPE::WORLD_SCENE ) ] = new WorldScene( );
	sceneList_[ static_cast<UINT>( SCENE_TYPE::WORLD_SCENE ) ]->setSceneName( L"World Scene" );

	// 현재 Scene 설정
<<<<<<< HEAD
	currScene_ = sceneList_[ static_cast<UINT>( SCENE_TYPE::TITLE_SCENE ) ];
	currSceneType_ = SCENE_TYPE::TITLE_SCENE;
	currScene_->entry( );
=======
	currScene_ = sceneList_[ static_cast<UINT>( SCENE_TYPE::TITLE_SCENE) ];
	currScene_->Entry( );
>>>>>>> 4a7d3951422e1aa00ff62c3f7f8d77d88525af52
}
