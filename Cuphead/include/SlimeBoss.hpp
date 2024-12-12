#ifndef SLIME_BOSS_HPP
#define SLIME_BOSS_HPP

#include "Object.hpp"
#include "Texture.hpp"

enum phase {
	Phase1,
	Phase2,
	Phase3
};



class SlimeBoss : public Object {
public:
	SlimeBoss();
	virtual ~SlimeBoss() {}

	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void onCollision(Object* other) override;
	virtual void onCollisionEntry(Object* other) override;
	virtual void onCollisionExit(Object* other) override;

	

	virtual SlimeBoss* clone() override {
		return new SlimeBoss(*this);
	}




};

#endif // SLIME_BOSS_HPP