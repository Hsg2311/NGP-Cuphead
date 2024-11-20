#include "EventHandler.hpp"
#include "Object.hpp"
#include "SceneHandler.hpp"
#include "Scene.hpp"
#include <ranges>
#include <algorithm>

EventHandler::EventHandler( ) : events_{ }, deadObjects_{ } {}

EventHandler::~EventHandler( ) {}

void EventHandler::update( ) {
	// 이전 프레임에서 등록해둔 Dead Object들 삭제
	std::ranges::for_each( deadObjects_, []( auto obj ) {
		delete obj;
	} );

	deadObjects_.clear( );
	
	// Event 처리
	std::ranges::for_each( events_, [this]( const auto& event ) {
		excute( event );
	} );

	events_.clear( );
}

void EventHandler::excute( const Event& event ) {
	switch ( event.eventType ) {
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// wParam : Group Type
		// lParam : Object Pointer
		auto groupType = static_cast<GROUP_TYPE>( event.wParam );
		auto obj = reinterpret_cast<Object*>( event.lParam );

		SceneHandler::getInst( ).getCurrScene( )->addObject( groupType, obj );
	}
		break;

	case EVENT_TYPE::DESTROY_OBJECT:
	{
		auto obj = reinterpret_cast<Object*>( event.lParam );
		obj->alive_ = false;
		deadObjects_.emplace_back( obj );
	}
		break;

	case EVENT_TYPE::CHANGE_SCENE:
		SceneHandler::getInst( ).changeScene( static_cast<SCENE_TYPE>( event.wParam ) );
		break;
	}
}
