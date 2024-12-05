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
	
	void sendRegisterPacket(ObjectName objectname, std::uint16_t id);
};

#endif // WORLD_SCENE_HPP


