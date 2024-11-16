#include "OverWorldPlayer.hpp"
#include "struct.hpp"
#include "Timer.hpp"
#include "InputDeviceHandler.hpp"

#include "Texture.hpp"
#include "ResourceHandler.hpp"
#include "func.hpp"

#include "SceneHandler.hpp"

OverWorldPlayer::OverWorldPlayer() {
	CreateCollider();
	getCollider()->setScale(Vec2{ 50.f, 50.f });

	auto player = ResourceHandler::GetInst().LoadTexture(L"OverWorldPlayer_Texture", L"/texture/overworld/Cuphead.png");
	
	CreateAnimator();
	getAnimator()->createAnimation(L"OverWorldPlayer", player, Vec2{ 0.f, 550.f }, Vec2{ 100.f, 110.f }, Vec2{ 100.f, 0.f }, 0.1f, 9);
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
	SceneHandler::GetInst().SetCameraPos(objPos);
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
