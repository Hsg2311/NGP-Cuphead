#ifndef STAGE_PLAYER_HPP
#define STAGE_PLAYER_HPP

#include "Object.hpp"
class StagePlayer : public Object
{
	StagePlayer();
	virtual ~StagePlayer() {}

	virtual void update() override;

	virtual void onCollision(Object* other) override;
	virtual void onCollisionEntry(Object* other) override;
	virtual void onCollisionExit(Object* other) override;

	virtual StagePlayer* clone() override {
		return new StagePlayer(*this);
	}
};

#endif //STAGE_PLAYER_HPP