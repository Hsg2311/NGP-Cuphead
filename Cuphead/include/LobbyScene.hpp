#ifndef LOBBYSCENE_HPP
#define LOBBYSCENE_HPP

#include "Scene.hpp"

class LobbyScene : public Scene {
public:
	LobbyScene( ) {}
	virtual ~LobbyScene( ) {}

	virtual void update( ) override { Scene::update( ); }
	virtual void entry( ) override;
	virtual void exit( ) override { Scene::destroyObjGroupList( ); }

	virtual void handlePacket( const Packet& packet ) override {}
};

#endif // LOBBYSCENE_HPP