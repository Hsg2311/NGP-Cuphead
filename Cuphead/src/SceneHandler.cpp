#include "SceneHandler.hpp"
#include "Start_Scene.hpp"
#include "Tool_Scene.hpp"
#include "Square_Scene.hpp"

#include "Boss1_Scene.hpp"

SceneHandler::SceneHandler( )
	: sceneList_{ }
	, currScene_{ nullptr }
{}

SceneHandler::~SceneHandler( ) {
	for ( auto& scene : sceneList_ ) {
		delete scene;
	}
}

void SceneHandler::init( ) {
	// Scene ����
	sceneList_[ static_cast<UINT>( SCENE_TYPE::START_SCENE ) ] = new Start_Scene{ };
	sceneList_[ static_cast<UINT>( SCENE_TYPE::START_SCENE ) ]->setSceneName( L"Start Scene" );

	sceneList_[ static_cast<UINT>( SCENE_TYPE::TOOL_SCENE ) ] = new Tool_Scene{ };
	sceneList_[ static_cast<UINT>( SCENE_TYPE::TOOL_SCENE ) ]->setSceneName( L"Tool Scene" );

	sceneList_[static_cast<UINT>(SCENE_TYPE::SQUARE_SCENE)] = new Square_Scene{ };
	sceneList_[static_cast<UINT>(SCENE_TYPE::SQUARE_SCENE)]->setSceneName(L"Square Scene");

	sceneList_[static_cast<UINT>(SCENE_TYPE::BOSS1_SCENE)] = new Boss1_Scene{ };
	sceneList_[static_cast<UINT>(SCENE_TYPE::BOSS1_SCENE)]->setSceneName(L"Boss1 Scene");

	// ���� Scene ����
	currScene_ = sceneList_[ static_cast<UINT>( SCENE_TYPE::BOSS1_SCENE) ];
	currScene_->Entry( );


}
	