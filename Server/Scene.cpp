#include "Object.hpp"
#include "Scene.hpp"
#include <ranges>
#include <algorithm>

Scene::Scene( )
	: objGroupList_{ }
	, sceneName_{ }
{}

Scene::~Scene( ) {
	// Scene�� ��ϵ� Object���� delete
	std::ranges::for_each( objGroupList_, []( auto& objs ) {
		std::ranges::for_each( objs, []( auto obj ) {
			delete obj;
		} );
	} );
}

void Scene::update( ) {
	// Scene�� ��ϵ� Object���� update
	std::ranges::for_each( objGroupList_, []( auto& objs ) {
		std::ranges::for_each( objs, []( auto obj ) {
			if( obj->isAlive( ) )
				obj->update( );
		} );
	} );
}

void Scene::componentUpdate( ) {
	// Scene�� ��ϵ� Object���� componentUpdate
	std::ranges::for_each( objGroupList_, []( auto& objs ) {
		std::ranges::for_each( objs, []( auto obj ) {
			obj->componentUpdate( );
		} );
	} );
}