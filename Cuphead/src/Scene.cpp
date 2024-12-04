#include "Object.hpp"
#include "Scene.hpp"
#include "PacketQueue.hpp"
#include "SendingStorage.hpp"
#include <ranges>
#include <algorithm>

Scene::Scene( )
	: objGroupList_{ }
	, sceneName_{ }
{
	std::ranges::for_each(objGroupList_, [](auto& objs) {
		std::ranges::for_each(objs, [](auto obj) {
			PacketQueue::getInst().addObject(obj);
			
			Packet packet;
			packet.type = PacketType::REGIST;
			packet.rs.groupType = obj->getGroup();
			packet.rs.id = obj->getId();

			SendingStorage::getInst().pushPacket(packet);
			
		});
	});
}

Scene::~Scene( ) {
	// Scene에 등록된 Object들을 delete
	std::ranges::for_each( objGroupList_, []( auto& objs ) {
		std::ranges::for_each( objs, []( auto obj ) {
			PacketQueue::getInst().deleteObject(obj);
			delete obj;
		} );
	} );
}

void Scene::update( ) {
	// Scene에 등록된 Object들을 update
	std::ranges::for_each( objGroupList_, []( auto& objs ) {
		std::ranges::for_each( objs, []( auto obj ) {
			if( obj->isAlive( ) )
				obj->update( );
		} );
	} );
}

void Scene::componentUpdate( ) {
	// Scene에 등록된 Object들을 componentUpdate
	std::ranges::for_each( objGroupList_, []( auto& objs ) {
		std::ranges::for_each( objs, []( auto obj ) {
			obj->componentUpdate( );
		} );
	} );
}

void Scene::render( HDC hdc ) {
	// Scene에 등록된 Object들을 render
	for ( auto& group : objGroupList_ ) {
		for ( auto iter = group.begin( ); iter != group.end( ); ) {
			if ( ( *iter )->isAlive( ) ) {
				( *iter )->render( hdc );
				++iter;
			}
			else {
				iter = group.erase( iter );
			}
		}
	}
}
