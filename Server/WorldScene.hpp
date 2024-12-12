#ifndef WORLD_SCENE_HPP
#define WORLD_SCENE_HPP

#include "Scene.hpp"

class WorldScene : public Scene {
public:
	WorldScene( ) {}
	virtual ~WorldScene( ) {}

	virtual void update( ) override { Scene::update( ); }
	virtual void entry( ) override;
	virtual void exit( ) override { Scene::destroyObjGroupList( ); }

	virtual void handlePacket( const Packet& packet ) override;

private:
	void handleInputPacket( const Packet& packet );
};

#endif // WORLD_SCENE_HPP