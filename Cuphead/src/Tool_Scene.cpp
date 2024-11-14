#include "Tool_Scene.hpp"
#include "InputDeviceHandler.hpp"

Tool_Scene::Tool_Scene( ) {
}

Tool_Scene::~Tool_Scene( ) {
}

void Tool_Scene::update( ) {
	Scene::update( );

	if ( KEY_TAP( InputData::Q ) ) {
		ChangeScene( SCENE_TYPE::START_SCENE );
	}
}

void Tool_Scene::Entry( ) {
}

void Tool_Scene::Exit( ) {
}

//void Tool_Scene::update( ) {
//}