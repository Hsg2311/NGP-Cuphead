#include "Boss1.hpp"
#include "Timer.hpp"
#include "func.hpp"
#include "ResourceHandler.hpp"
#include <cmath>

Boss1::Boss1()
{
	CreateCollider();
	getCollider()->setScale(Vec2{ 521.6f, 460.f });

	

	auto tex = ResourceHandler::GetInst().LoadTexture(L"Boss1_Intro", L"/texture/boss1/boss/Intro.png");

	CreateAnimator();
	getAnimator()->createAnimation(L"Boss1_Intro", tex, Vec2{ 0.f, 0.f }, Vec2{ 815.f, 721.f }, Vec2{ 815.f, 0.f }, 0.07f, 20); // 815, 721
	getAnimator()->play(L"Boss1_Intro");

}

Boss1::~Boss1()
{
}

void Boss1::update() {
	auto objPos = getObjPos();



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
