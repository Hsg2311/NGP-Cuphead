#ifndef SLIME_BOSS_SCENE_HPP
#define SLIME_BOSS_SCENE_HPP

#include "Scene.hpp"

class SlimeBossScene : public Scene {
public:
	SlimeBossScene() {}
	virtual ~SlimeBossScene() {}

	virtual void update() override { Scene::update(); }
	virtual void entry() override;
	virtual void exit() override { Scene::destroyObjGroupList(); }

	virtual void handlePacket(const Packet& packet) override;

private:
	void handleInputPacket(const Packet& packet);
};

#endif // SLIME_BOSS_SCENE_HPP