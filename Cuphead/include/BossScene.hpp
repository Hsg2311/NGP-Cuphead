#ifndef BOSS_SCENE_HPP
#define BOSS_SCENE_HPP

#include "Scene.hpp"

class BossScene : public Scene {
public:
	BossScene() {}
	virtual ~BossScene() {}

	virtual void update() override { Scene::update(); }
	virtual void entry() override;
	virtual void exit() override { Scene::destroyObjGroupList(); }

	void sendRegisterPacket(ObjectName objectname, std::uint16_t id);
};

#endif // BOSS_SCENE_HPP


