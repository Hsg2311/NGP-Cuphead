#include "OverWorldPlayer.hpp"
#include "struct.hpp"
#include "Timer.hpp"
#include "InputDeviceHandler.hpp"
#include "Texture.hpp"
#include "ResourceHandler.hpp"
#include "Projectile.hpp"
#include "func.hpp"

OverWorldPlayer::OverWorldPlayer() {
	CreateCollider();
	getCollider()->setScale(Vec2{ 100.f, 100.f });

	auto tex = ResourceHandler::GetInst().LoadTexture(L"Player_Texture", L"/texture/idle/cuphead_idle.png");
	CreateAnimator();
	getAnimator()->createAnimation(L"Player_Idle", tex, Vec2{ 0.f, 0.f }, Vec2{ 100.f, 155.f }, Vec2{ 100.f, 0.f }, 0.065f, 9);
	getAnimator()->play(L"Player_Idle");
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
	if (KEY_TAP(InputData::Z)) {
		CreateProjectile();
	}

	setObjPos(objPos);
}

void OverWorldPlayer::render(HDC hdc) {
	componentRender(hdc);
}

void OverWorldPlayer::CreateProjectile() {
	auto playerPos = getObjPos();
	playerPos.y -= getObjScale().y / 2.f;

	Projectile* projectile = new Projectile{ };
	projectile->setObjName(L"Player_Projectile");
	projectile->setObjPos(playerPos);
	projectile->setObjScale(Vec2{ 30.f, 30.f });
	projectile->setDirection(Vec2(0.f, 1.f));

	CreateObject(GROUP_TYPE::PLAYER_PROJECTILE, projectile);
};

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
