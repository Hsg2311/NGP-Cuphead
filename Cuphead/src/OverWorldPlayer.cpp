#include "OverWorldPlayer.hpp"
#include "struct.hpp"
#include "Timer.hpp"
#include "InputDeviceHandler.hpp"
#include "Texture.hpp"
#include "ResourceHandler.hpp"
#include "func.hpp"

OverWorldPlayer::OverWorldPlayer() {
	CreateCollider();
	getCollider()->setScale(Vec2{ 100.f, 100.f });

	//auto player = ResourceHandler::GetInst().LoadTexture(L"OverWorldPlayer_Texture", L"/texture/idle/cuphead_idle.png");
	auto player = ResourceHandler::GetInst().LoadTexture(L"OverWorldPlayer_Texture", L"texture/overworld/Cuphead.png");
	CreateAnimator();
	getAnimator()->createAnimation(L"OverWorldPlayer", player, Vec2{ 0.f, 440.f }, Vec2{ 100.f, 110.f }, Vec2{ 100.f, 0.f }, 1.f, 9);
	getAnimator()->play(L"OverWorldPlayer");
}

OverWorldPlayer::~OverWorldPlayer()
{}

void OverWorldPlayer::update() {
	Vec2 objPos = getObjPos();

	if (KEY_HOLD(InputData::LEFT)) {
		objPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(InputData::RIGHT)) {
		objPos.x += 200.f * fDT;
	}
	if (KEY_HOLD(InputData::UP)) {
		objPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(InputData::DOWN)) {
		objPos.y += 200.f * fDT;
	}

	setObjPos(objPos);
}

void OverWorldPlayer::render(HDC hdc) {
	componentRender(hdc);
}


void OverWorldPlayer::OnCollision(Object* other)
{
}

void OverWorldPlayer::OnCollisionEntry(Object* other)
{
	getCollider()->addCollisionCount();
}

void OverWorldPlayer::OnCollisionExit(Object* other)
{
	getCollider()->subCollisionCount();
}
