#pragma once

#ifndef __BOSS1_HPP
#define __BOSS1_HPP

#include "Object.hpp"
#include "struct.hpp"
#include <Windows.h>

class Boss1 : public Object {
public:
	Boss1();
	virtual ~Boss1();

public:

	void setCenterPos(const Vec2& centerPos) { centerPos_ = centerPos; }

public:
	virtual void update() override;
	virtual void render(HDC hdc) override;

public:
	virtual void OnCollision(Object* other) override;
	virtual void OnCollisionEntry(Object* other) override;
	virtual void OnCollisionExit(Object* other) override;

public:
	virtual Boss1* clone() override { return new Boss1{ *this }; }

private:
	Vec2 centerPos_;
	float speed_;
	float maxDistance_;
	int dir_;
	int hp_;
};

#endif // __BOSS1_HPP