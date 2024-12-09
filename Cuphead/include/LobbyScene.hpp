#pragma once
#ifndef LOBBY_SCENE_HPP
#define LOBBY_SCENE_HPP

#include "Scene.hpp"

class LobbyScene : public Scene {
public:
	LobbyScene() {}
	virtual ~LobbyScene() {}

	virtual void update() override { Scene::update(); }
	virtual void entry() override;
	
	virtual void exit() override { Scene::destroyObjGroupList(); }
};

#endif // WORLD_SCENE_HPP