#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "Scene.hpp"

class MenuScene : public Scene {
public:
	MenuScene( ) {}
	virtual ~MenuScene( ) {}

	virtual void update( ) override { Scene::update( ); }
	virtual void entry( ) override;
	virtual void exit( ) override { Scene::destroyObjGroupList( ); }

	virtual void handlePacket( const Packet& packet ) override;

private:
	void handleLoginResultPacket( const Packet& packet );
};

#endif // MENU_SCENE_HPP