#ifndef SLIME_BOSS_HPP
#define SLIME_BOSS_HPP

#include "Object.hpp"

enum phase {
	Phase1,
	Phase2,
	Phase3
};

enum patturn {
	Intro,
	LJump,
	LUpJump,
	LDownJump,
	LAttack,
	RJump,
	RUpJump,
	RDownJump,
	RAttack,

};

class SlimeBoss : public Object {
public:
	SlimeBoss();
	virtual ~SlimeBoss() {}



	virtual void update() override;
	

	virtual void onCollision(Object* other) override;
	virtual void onCollisionEntry(Object* other) override;
	virtual void onCollisionExit(Object* other) override;

	void PaturnUpdate();
	void TimeCheck();

	void SendAnimPacket(PacketType packet, AnimationRPC::Type type);

	virtual SlimeBoss* clone() override {
		return new SlimeBoss(*this);
	}

private:


	int count{};
	int dir{ 1 };
	float Time{};
	Vec2 jumpStartPos{};
	Vec2 objPos{};
	patturn Patturn;
	phase Phase;

};

#endif // BOSS_HPP