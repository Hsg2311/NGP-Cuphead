#pragma once
#include "Object.hpp"


class Bullet : public Object
{
public:
	Bullet(Vec2 charPos, Direction dir);
	virtual ~Bullet();

	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void onCollision(Object* other) override;
	virtual void onCollisionEntry(Object* other) override;
	virtual void onCollisionExit(Object* other) override;

	virtual Bullet* clone() override { return new Bullet{ *this }; }
private:
	float bulletSpeed = 10.f;
};

