#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Object.hpp"

class Player : public Object {
public:
	Player();
	virtual ~Player() {}

	virtual void update() override;

	virtual void onCollision(Object* other) override;
	virtual void onCollisionEntry(Object* other) override;
	virtual void onCollisionExit(Object* other) override;

	virtual Player* clone() override {
		return new Player(*this);
	}
};

#endif // OVERWORLD_PLAYER_HPP