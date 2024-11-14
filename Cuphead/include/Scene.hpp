#ifndef __SCENE_HPP
#define __SCENE_HPP

#include "Object.hpp"
#include "define.hpp"
#include "func.hpp"
#include "EventHandler.hpp"
#include <array>
#include <string>
#include <vector>
#include <Windows.h>
#include <ranges>
#include <algorithm>

class Scene {
public:
	Scene( );
	virtual ~Scene( ) = 0;

public:
	void setSceneName( const std::wstring& sceneName ) { sceneName_ = sceneName; }
	const std::wstring& getSceneName( ) const { return sceneName_; }

public:
	virtual void update( );
	void componentUpdate( );
	virtual void render( HDC hdc );

public:
	virtual void Entry( ) = 0;
	virtual void Exit( ) = 0;

public:
	void addObject( GROUP_TYPE groupType, Object* obj ) {
		objGroupList_[ static_cast<UINT>( groupType ) ].emplace_back( obj );
	}

	const std::vector<Object*>& getGroup( GROUP_TYPE groupType ) const {
		return objGroupList_[ static_cast<UINT>( groupType ) ];
	}

	void destroyObjGroupList( ) {
		std::ranges::for_each( objGroupList_, []( auto& group ) {
			Safe_Delete_Vector( group );
		} );
	}

	void ChangeScene( SCENE_TYPE sceneType ) {
		auto event = Event{
			.eventType = EVENT_TYPE::CHANGE_SCENE,
			.wParam = static_cast<DWORD_PTR>( sceneType )
		};

		EventHandler::GetInst( ).addEvent( event );
	}

private:
	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	std::array<std::vector<Object*>, static_cast<UINT>( GROUP_TYPE::EOE )> objGroupList_;
	std::wstring sceneName_;
};

#endif // __SCENE_HPP