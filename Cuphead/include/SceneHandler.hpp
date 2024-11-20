#ifndef __SCENE_HANDLER_HPP
#define __SCENE_HANDLER_HPP

#include "define.hpp"
#include "Scene.hpp"
#include <array>
#include <Windows.h>

class EventHandler;

class SceneHandler {
	SINGLETON( SceneHandler );

public:
	void init( );
	void update( ) {
		currScene_->update( );
		currScene_->componentUpdate( );
	}
	void render( HDC hdc ) { 
		currScene_->render( hdc ); 
		
	}

public:
	std::wstring scenename{};
	Scene* getCurrScene( ) const { return currScene_; }
	std::wstring checkSceneName() { return scenename; }
	void setSceneName(std::wstring name) { scenename = name; }
private:
	void changeScene( SCENE_TYPE sceneType ) {
		currScene_->Exit( );

		currScene_ = sceneList_[ static_cast<UINT>( sceneType ) ];
		
		currScene_->Entry( );
	}

	friend class EventHandler;

private:
	std::array<Scene*, static_cast<UINT>( SCENE_TYPE::EOE )> sceneList_;
	Scene* currScene_;

public:
	Vec2 GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vec2 pos) { _cameraPos = pos; }


private:
	Vec2 _cameraPos = { 0,0 };
};

#endif // __SCENE_HANDLER_HPP