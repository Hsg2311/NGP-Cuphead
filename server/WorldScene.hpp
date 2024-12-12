#ifndef WORLD_SCENE_HPP
#define WORLD_SCENE_HPP

#include "Scene.hpp"
#include "Texture.hpp"
#include "ResourceHandler.hpp"

class WorldScene : public Scene {
public:
	WorldScene( )
		: tex_( ResourceHandler::getInst( ).loadTexture( L"Pixel Map", L"\\pixel_map.png" ) ) {}
	virtual ~WorldScene( ) {}

	virtual void update( ) override { Scene::update( ); }
	virtual void entry( ) override;
	virtual void exit( ) override { Scene::destroyObjGroupList( ); }

	virtual void handlePacket( const Packet& packet ) override;

private:
	void handleInputPacket( const Packet& packet );

	Texture* tex_;
};

#endif // WORLD_SCENE_HPP