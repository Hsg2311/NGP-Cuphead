#include "SlimeBoss.hpp"
#include "ResourceHandler.hpp"
#include "PacketQueue.hpp"
SlimeBoss::SlimeBoss()
{
	//phase 1
	{
		auto Ljump = ResourceHandler::getInst().loadTexture(L"Ljump", L"/texture/smileBoss/Phase1/jump/Ljump.png");
		auto Lupjump = ResourceHandler::getInst().loadTexture(L"Lupjump", L"/texture/smileBoss/Phase1/jump/Lupjump.png");
		auto Ldownjump = ResourceHandler::getInst().loadTexture(L"Ldownjump", L"/texture/smileBoss/Phase1/jump/Ldownjump.png");
		auto LAttack = ResourceHandler::getInst().loadTexture(L"LAttack", L"/texture/smileBoss/Phase1/Attack/LAttack.png");
		auto LPhaseTurn = ResourceHandler::getInst().loadTexture(L"LPhaseTurn", L"/texture/smileBoss/Phase1/LPhaseTurn.png");



		auto Rjump = ResourceHandler::getInst().loadTexture(L"Rjump", L"/texture/smileBoss/Phase1/jump/Rjump.png");
		auto Rupjump = ResourceHandler::getInst().loadTexture(L"Rupjump", L"/texture/smileBoss/Phase1/jump/Rupjump.png");
		auto Rdownjump = ResourceHandler::getInst().loadTexture(L"Rdownjump", L"/texture/smileBoss/Phase1/jump/Rdownjump.png");
		auto RAttack = ResourceHandler::getInst().loadTexture(L"RAttack", L"/texture/smileBoss/Phase1/Attack/RAttack.png");
		auto RPhaseTurn = ResourceHandler::getInst().loadTexture(L"RPhaseTurn", L"/texture/smileBoss/Phase1/RPhaseTurn.png");



		getAnimator()->createAnimation(L"Ljump", Ljump, Vec2{ 0.f, 0.f }, Vec2{ 290.f, 200.f }, Vec2{ 290.f, 0.f }, 0.05f, 9); //290.f 200.f
		getAnimator()->createAnimation(L"Lupjump", Lupjump, Vec2{ 0.f, 0.f }, Vec2{ 220.f, 200.f }, Vec2{ 220.f, 0.f }, 0.05f, 3); //220.f 200.f
		getAnimator()->createAnimation(L"Ldownjump", Ldownjump, Vec2{ 0.f, 0.f }, Vec2{ 200.f, 200.f }, Vec2{ 200.f, 0.f }, 0.05f, 3); //200.f 200.f
		getAnimator()->createAnimation(L"LAttack", LAttack, Vec2{ 0.f, 0.f }, Vec2{ 1300.f, 700.f }, Vec2{ 1300.f, 0.f }, 0.1f, 16); //200.f 200.f
		getAnimator()->createAnimation(L"LPhaseTurn", LPhaseTurn, Vec2{ 0.f, 0.f }, Vec2{ 600.f, 900.f }, Vec2{ 600.f, 0.f }, 0.1f, 48); //200.f 200.f

		getAnimator()->createAnimation(L"Rjump", Rjump, Vec2{ 0.f, 0.f }, Vec2{ 290.f, 200.f }, Vec2{ 290.f, 0.f }, 0.05f, 9); //290.f 200.f
		getAnimator()->createAnimation(L"Rupjump", Rupjump, Vec2{ 0.f, 0.f }, Vec2{ 220.f, 200.f }, Vec2{ 220.f, 0.f }, 0.05f, 3); //220.f 200.f
		getAnimator()->createAnimation(L"Rdownjump", Rdownjump, Vec2{ 0.f, 0.f }, Vec2{ 200.f, 200.f }, Vec2{ 200.f, 0.f }, 0.05f, 3); //220.f 200.f
		getAnimator()->createAnimation(L"RAttack", RAttack, Vec2{ 0.f, 0.f }, Vec2{ 1300.f, 700.f }, Vec2{ 1300.f, 0.f }, 0.1f, 16); //200.f 200.f
		getAnimator()->createAnimation(L"RPhaseTurn", RPhaseTurn, Vec2{ 0.f, 0.f }, Vec2{ 600.f, 900.f }, Vec2{ 600.f, 0.f }, 0.07f, 48); //200.f 200.f

	}


}


void SlimeBoss::update() {
	
	
}

void SlimeBoss::render(HDC hdc) {
	componentRender(hdc);
}

void SlimeBoss::onCollision(Object* other) {
}

void SlimeBoss::onCollisionEntry(Object* other) {
	getCollider()->addCollisionCount();
}

void SlimeBoss::onCollisionExit(Object* other) {
	getCollider()->subCollisionCount();
}


