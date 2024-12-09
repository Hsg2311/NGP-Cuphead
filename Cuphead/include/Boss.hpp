#ifndef BOSS_HPP
#define BOSS_HPP

#include "Object.hpp"
#include "Texture.hpp"

enum phase {
	Phase1,
	Phase2,
	Phase3
};

enum patturn {
	Intro,
	LPhaseTurn,
	RPhaseTurn,
	LJump,
	LUpJump,
	LDownJump,
	LAttack,
	RJump,
	RUpJump,
	RDownJump,
	RAttack,

	LJump_2,
	LUpJump_2,
	LDownJump_2,
	LAttack_2,
	RJump_2,
	RUpJump_2,
	RDownJump_2,
	RAttack_2
};

class Boss : public Object {
public:
	Boss();
	virtual ~Boss() {}

	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void onCollision(Object* other) override;
	virtual void onCollisionEntry(Object* other) override;
	virtual void onCollisionExit(Object* other) override;

	void PaturnUpdate();
	void TimeCheck();

	void PhaseTurn();


	virtual Boss* clone() override {
		return new Boss(*this);
	}

private:


	int count{};
	int dir{1};
	float Time{};
	Vec2 jumpStartPos{};
	Vec2 objPos{};
	patturn Patturn;
	phase Phase;

	std::vector<Texture*> textures_;
};

#endif // BOSS_HPP