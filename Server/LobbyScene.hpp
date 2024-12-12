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

	virtual void handlePacket( const Packet& packet ) override;

private:
	void handleLoginPacket( const Packet& packet );
	void handleTryGameStartPacket( const Packet& packet );
	void handleLeavePacket( const Packet& packet );
	void handleChangeSceneAckPacket( const Packet& packet );

	bool hasCupheadChangedScene_ = false;
	bool hasMugmanChangedScene_ = false;
};

#endif // LOBBYSCENE_HPP