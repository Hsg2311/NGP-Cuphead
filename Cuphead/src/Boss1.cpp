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
	firstTime = Timer::GetInst().getDT();
	getAnimator()->play(L"Boss1_Intro");
	firstPatturn = Intro;

	// 콘솔 확인 출력
	AllocConsole();

	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
}

Boss1::~Boss1()
{
}

void Boss1::update() {


	secondTime += Timer::GetInst().getDT();
	printf("secondTime : %lf | firstTime : %lf\n", secondTime, firstTime);

	TimeCheck();

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

void Boss1::PaturnUpdate() {

	firstPatturn = static_cast<patturn>(firstPatturn + 1);
	switch (firstPatturn) {
	case Idle:
		getAnimator()->play(L"Boss1_Idle");
		secondTime = {};
		break;
	case Attack1:
		getAnimator()->play(L"Boss1_Idle");
		secondTime = {};
		break;
	case Attack2:
		getAnimator()->play(L"Boss1_Idle");
		secondTime = {};
		firstPatturn = Idle;
		break;
	}


}

void Boss1::TimeCheck() {

	printf("secondTime : %lf | firstTime : %lf\n", secondTime, firstTime);

	switch (firstPatturn) {
	case Intro:
		if (secondTime - firstTime >= 4)
		{
			PaturnUpdate();
		}
		break;
	case Idle:
		if (secondTime - firstTime >= 4)
		{
			PaturnUpdate();
		}
		break;
	case Attack1:
		if (secondTime - firstTime >= 4)
		{
			PaturnUpdate();
		}
		break;
	case Attack2:
		if (secondTime - firstTime >= 4)
		{
			PaturnUpdate();
		}
		break;
	}


}