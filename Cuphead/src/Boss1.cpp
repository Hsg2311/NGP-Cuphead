#include "Boss1.hpp"
#include "Timer.hpp"
#include "func.hpp"
#include "ResourceHandler.hpp"
#include "InputDeviceHandler.hpp"
#include <cmath>

Boss1::Boss1()
{
	CreateCollider();
	getCollider()->setScale(Vec2{ 521.6f, 460.f });

	

	auto intro = ResourceHandler::GetInst().LoadTexture(L"Boss1_Intro", L"/texture/boss1/boss/Intro.png");
	auto idle = ResourceHandler::GetInst().LoadTexture(L"Boss1_Idle", L"/texture/boss1/boss/Idle.png");

	CreateAnimator();
	getAnimator()->createAnimation(L"Boss1_Intro", intro, Vec2{ 0.f, 0.f }, Vec2{ 815.f, 721.f }, Vec2{ 815.f, 0.f }, 0.07f, 20); // 815, 721
	getAnimator()->createAnimation(L"Boss1_Idle", idle, Vec2{ 0.f, 0.f }, Vec2{ 815.f, 721.f }, Vec2{ 815.f, 0.f }, 0.05f, 20); // 815, 721
	getAnimator()->play(L"Boss1_Intro");

}

Boss1::~Boss1()
{
}

void Boss1::update() {
	auto objPos = getObjPos();
	if (KEY_TAP(InputData::E)) {
		
		getAnimator()->play(L"Boss1_Idle");
	}


	setObjPos(objPos);
}

void Boss1::render(HDC hdc) {
	Object::render(hdc);
}

void Boss1::OnCollision(Object* other)
{
}

void Boss1::OnCollisionEntry(Object* other)
{
	getCollider()->addCollisionCount();

	if (other->getObjName() == L"Player_Projectile") {
		--hp_;

		if (hp_ <= 0) {
			DestroyObject(this);
		}
	}
}

void Boss1::OnCollisionExit(Object* other)
{
	getCollider()->subCollisionCount();
}
