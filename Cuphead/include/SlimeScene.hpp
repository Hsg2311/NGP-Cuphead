#ifndef SLIME_SCENE_HPP
#define SLIME_SCENE_HPP

#include "Scene.hpp"

class SlimeScene : public Scene {
public:
	SlimeScene() {}
	virtual ~SlimeScene() {}

	virtual void update() override { Scene::update(); }
	virtual void entry() override;
	virtual void exit() override { Scene::destroyObjGroupList(); }

	virtual void handlePacket(const Packet& packet) override;


private:
	void handleRegisterPacket(const Packet& packet);
	void handleDestroyPacket(const Packet& packet);
	void handleMovePacket(const Packet& packet);
	void handleAnimationRPCPacket(const Packet& packet);
};

#endif // WORLD_SCENE_HPP