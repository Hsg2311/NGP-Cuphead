#include "Boss.hpp"
#include "ResourceHandler.hpp"
#include "Camera.hpp"
#include "InputDeviceHandler.hpp"
#include "Timer.hpp"
#include "protocol.hpp"
#include "SendingStorage.hpp"

#include <ranges>
#include <algorithm>
#include <cmath>

#define pie 3.14

Boss::Boss() {
	createCollider();
	getCollider()->setScale(Vec2{ 200.f, 200.f });
	createAnimator();

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
	
	// phase2
	{
		auto Ljump_2 = ResourceHandler::getInst().loadTexture(L"Ljump_2", L"/texture/smileBoss/Phase2/jump/Ljump.png");
		auto Lupjump_2 = ResourceHandler::getInst().loadTexture(L"Lupjump_2", L"/texture/smileBoss/Phase2/jump/LJumpUp.png");
		auto Ldownjump_2 = ResourceHandler::getInst().loadTexture(L"Ldownjump_2", L"/texture/smileBoss/Phase2/jump/LJumpdown.png");
		auto Lattack_2 = ResourceHandler::getInst().loadTexture(L"Lattack_2", L"/texture/smileBoss/Phase2/LAttack.png");

		auto Rjump_2 = ResourceHandler::getInst().loadTexture(L"Rjump_2", L"/texture/smileBoss/Phase2/jump/Rjump.png");
		auto Rupjump_2 = ResourceHandler::getInst().loadTexture(L"Rupjump_2", L"/texture/smileBoss/Phase2/jump/RJumpUp.png");
		auto Rdownjump_2 = ResourceHandler::getInst().loadTexture(L"Rdownjump_2", L"/texture/smileBoss/Phase2/jump/RJumpdown.png");
		auto Rattack_2 = ResourceHandler::getInst().loadTexture(L"Rattack_2", L"/texture/smileBoss/Phase2/RAttack.png");




		getAnimator()->createAnimation(L"Ljump_2", Ljump_2, Vec2{ 0.f, 0.f }, Vec2{ 500.f, 800.f }, Vec2{ 500.f, 0.f }, 0.05f, 8); //290.f 200.f
		getAnimator()->createAnimation(L"Lupjump_2", Lupjump_2, Vec2{ 0.f, 0.f }, Vec2{ 400.f, 400.f }, Vec2{ 400.f, 0.f }, 0.05f, 4); //220.f 200.f
		getAnimator()->createAnimation(L"Ldownjump_2", Ldownjump_2, Vec2{ 0.f, 0.f }, Vec2{ 400.f, 400.f }, Vec2{ 400.f, 0.f }, 0.05f, 5); //200.f 200.f
		getAnimator()->createAnimation(L"Lattack_2", Lattack_2, Vec2{ 0.f, 0.f }, Vec2{ 1280.f, 800.f }, Vec2{ 1280.f, 0.f }, 0.07f, 19); //200.f 200.f
	
		getAnimator()->createAnimation(L"Rjump_2", Rjump_2, Vec2{ 0.f, 0.f }, Vec2{ 500.f, 800.f }, Vec2{ 500.f, 0.f }, 0.05f, 8); //290.f 200.f
		getAnimator()->createAnimation(L"Rupjump_2", Rupjump_2, Vec2{ 0.f, 0.f }, Vec2{ 400.f, 400.f }, Vec2{ 400.f, 0.f }, 0.05f, 4); //220.f 200.f
		getAnimator()->createAnimation(L"Rdownjump_2", Rdownjump_2, Vec2{ 0.f, 0.f }, Vec2{ 400.f, 400.f }, Vec2{ 400.f, 0.f }, 0.05f, 5); //220.f 200.f
		getAnimator()->createAnimation(L"Rattack_2", Rattack_2, Vec2{ 0.f, 0.f }, Vec2{ 1280.f, 800.f }, Vec2{ 1280.f, 0.f }, 0.07f, 19); //200.f 200.f
		
	}




	Phase = Phase1;
	Patturn = LJump;
	getAnimator()->play(L"Ljump");
}

void Boss::update() {
	Time += Timer::getInst().getDT();

	TimeCheck();
	PhaseTurn();
}

void Boss::render(HDC hdc) {
	componentRender(hdc);
}

void Boss::onCollision(Object* other) {
}

void Boss::onCollisionEntry(Object* other) {
	getCollider()->addCollisionCount();
}

void Boss::onCollisionExit(Object* other) {
	getCollider()->subCollisionCount();
}

void Boss::PaturnUpdate() {
	//phase 1
	switch (Patturn) {
	case LPhaseTurn:
		getAnimator()->play(L"LPhaseTurn");
		Time = {};
		break;
	case RPhaseTurn:
		getAnimator()->play(L"RPhaseTurn");
		Time = {};
		break;
	case LJump:
		getAnimator()->play(L"Ljump");
		Time = {};
		break;
	case LUpJump:
		getAnimator()->play(L"Lupjump");
		Time = {};
		break;
	case LDownJump:
		getAnimator()->play(L"Ldownjump");
		Time = {};
		break;
	case LAttack:
		getAnimator()->play(L"LAttack");
		Time = {};
		break;

	case RJump:
		getAnimator()->play(L"Rjump");
		Time = {};
		break;
	case RUpJump:
		getAnimator()->play(L"Rupjump");
		Time = {};
		break;
	case RDownJump:
		getAnimator()->play(L"Rdownjump");
		Time = {};
		break;
	case RAttack:
		getAnimator()->play(L"RAttack");
		Time = {};
		break;


	case LJump_2:
		getAnimator()->play(L"Ljump_2");
		Time = {};
		break;
	case LUpJump_2:
		getAnimator()->play(L"Lupjump_2");
		Time = {};
		break;
	case LDownJump_2:
		getAnimator()->play(L"Ldownjump_2");
		Time = {};
		break;
	case LAttack_2:
		getAnimator()->play(L"Lattack_2");
		Time = {};
		break;

	case RJump_2:
		getAnimator()->play(L"Rjump_2");
		Time = {};
		break;
	case RUpJump_2:
		getAnimator()->play(L"Rupjump_2");
		Time = {};
		break;
	case RDownJump_2:
		getAnimator()->play(L"Rdownjump_2");
		Time = {};
		break;
	case RAttack_2:
		getAnimator()->play(L"Rattack_2");
		Time = {};
		break;
	}



}

void Boss::TimeCheck() {
	switch (Phase) {
	case Phase1:
	{
		const float jumpDuration = 0.45f; // 애니메이션 시간

		//phase1
		switch (Patturn) {
		case LJump: // 점프 준비 동작

			if (Time >= jumpDuration) { // 애니메이션 끝남
				Patturn = LUpJump;
				PaturnUpdate();
			}
			else {
				jumpStartPos = getObjPos();
			}
			break;
		case LUpJump: // 점프 올라가는 중	
		{
			Vec2 Pos1{};
			Pos1.x = jumpStartPos.x - Time / jumpDuration / 2 * 400 * dir;
			Pos1.y = jumpStartPos.y - sin(pie * Time / jumpDuration / 2) * 300;

			if (Pos1.x < 100.f || Pos1.x > 1180.f) {
				jumpStartPos.x = Pos1.x;
				dir *= -1;
				count += 1;
				getAnimator()->play(L"Rupjump");
			}

			setObjPos(Pos1);


			if (Time >= jumpDuration) { // 애니메이션 끝남
				jumpStartPos.x = Pos1.x;

				if (dir == 1) {
					Patturn = LDownJump;
					PaturnUpdate();
				}
				else {
					Patturn = RDownJump;
					PaturnUpdate();
				}

			}
		}
		break;

		case LDownJump: // 점프 내려가는 중
		{
			Vec2 Pos2{};
			Pos2.x = jumpStartPos.x - Time / jumpDuration / 2 * 400 * dir;
			Pos2.y = jumpStartPos.y - cos(pie * Time / jumpDuration / 2) * 300;

			if (Pos2.x < 100.f || Pos2.x > 1180.f) {
				jumpStartPos.x = Pos2.x;
				dir *= -1;
				count += 1;
				getAnimator()->play(L"Rdownjump");
			}

			setObjPos(Pos2);;
			if (Time >= jumpDuration) { // 애니메이션 끝남

				if (count == 3) {
					count = 0;
					if (dir == -1) {
						Patturn = RAttack;
						PaturnUpdate();
					}

					else {
						Patturn = LAttack;
						PaturnUpdate();
					}
				}
				else {
					if (dir == 1) {
						Patturn = LJump;
						PaturnUpdate();
					}
					else {
						Patturn = RJump;
						PaturnUpdate();
					}

				}


			}
		}
		break;

		case RJump: // 점프 준비 동작
			if (Time >= jumpDuration) { // 애니메이션 끝남
				Patturn = RUpJump;
				PaturnUpdate();
			}
			else {
				jumpStartPos = getObjPos();
			}
			break;
		case RUpJump: // 점프 올라가는 중
		{
			Vec2 Pos1{};
			Pos1.x = jumpStartPos.x - Time / jumpDuration / 2 * 400 * dir;
			Pos1.y = jumpStartPos.y - sin(pie * Time / jumpDuration / 2) * 300;

			if (Pos1.x < 100.f || Pos1.x > 1180.f) {
				jumpStartPos.x = Pos1.x;
				dir *= -1;
				count += 1;
				getAnimator()->play(L"Lupjump");
			}

			setObjPos(Pos1);
			if (Time >= jumpDuration) { // 애니메이션 끝남
				jumpStartPos.x = Pos1.x;
				if (dir == 1) {
					Patturn = LDownJump;
					PaturnUpdate();
				}
				else {
					Patturn = RDownJump;
					PaturnUpdate();
				}
			}
		}
		break;

		case RDownJump: // 점프 내려가는 중
		{
			Vec2 Pos2{};
			Pos2.x = jumpStartPos.x - Time / jumpDuration / 2 * 400 * dir;
			Pos2.y = jumpStartPos.y - cos(pie * Time / jumpDuration / 2) * 300;

			if (Pos2.x < 100.f || Pos2.x > 1180.f) {
				jumpStartPos.x = Pos2.x;
				dir *= -1;
				count += 1;
				getAnimator()->play(L"Ldownjump");
			}

			setObjPos(Pos2);;
			if (Time >= jumpDuration) { // 애니메이션 끝남

				if (count == 3) {
					count = 0;
					if (dir == -1) {
						Patturn = RAttack;
						PaturnUpdate();
					}

					else {
						Patturn = LAttack;
						PaturnUpdate();
					}
				}
				else {

					if (dir == 1) {
						Patturn = LJump;
						PaturnUpdate();
					}
					else {
						Patturn = RJump;
						PaturnUpdate();
					}
				}

			}
		}
		break;

		case LAttack:
			if (Time >= 1.6f)
			{
				Patturn = LJump;
				PaturnUpdate();
			}
			break;

		case RAttack:
			if (Time >= 1.6f)
			{
				Patturn = RJump;
				PaturnUpdate();
			}
			break;
		}
	}
		break;
	case Phase2: 

	{
		
		const float jumpDuration = 0.45f; // 애니메이션 시간
		//phase2
		switch (Patturn) {

		case RPhaseTurn:
			if (Time >= 4.8f) { // 애니메이션 끝남
				Patturn = RJump_2;
				PaturnUpdate();
			}
			break;

		case LPhaseTurn:
			if (Time >= 4.8f) { // 애니메이션 끝남
				Patturn = LJump_2;
				PaturnUpdate();
			}
			break;
		case LJump_2: // 점프 준비 동작

			if (Time >= 0.4f) { // 애니메이션 끝남
				Patturn = LUpJump_2;
				PaturnUpdate();
			}
			else {
				jumpStartPos = getObjPos();
			}
			break;
		case LUpJump_2: // 점프 올라가는 중	
		{
			Vec2 Pos1{};
			Pos1.x = jumpStartPos.x - Time / jumpDuration / 2 * 400 * dir;
			Pos1.y = jumpStartPos.y - sin(pie * Time / jumpDuration / 2) * 500;

			if (Pos1.x < 100.f || Pos1.x > 1180.f) {
				jumpStartPos.x = Pos1.x;
				dir *= -1;
				count += 1;
				getAnimator()->play(L"Rupjump_2");
			}

			setObjPos(Pos1);


			if (Time >= jumpDuration) { // 애니메이션 끝남
				jumpStartPos.x = Pos1.x;

				if (dir == 1) {
					Patturn = LDownJump_2;
					PaturnUpdate();
				}
				else {
					Patturn = RDownJump_2;
					PaturnUpdate();
				}

			}
		}
		break;

		case LDownJump_2: // 점프 내려가는 중
		{
			Vec2 Pos2{};
			Pos2.x = jumpStartPos.x - Time / jumpDuration / 2 * 400 * dir;
			Pos2.y = jumpStartPos.y - cos(pie * Time / jumpDuration / 2) * 500;

			if (Pos2.x < 100.f || Pos2.x > 1180.f) {
				jumpStartPos.x = Pos2.x;
				dir *= -1;
				count += 1;
				getAnimator()->play(L"Rdownjump_2");
			}

			setObjPos(Pos2);;
			if (Time >= jumpDuration) { // 애니메이션 끝남

				if (count == 3) {
					count = 0;
					if (dir == -1) {
						Patturn = RAttack_2;
						PaturnUpdate();
					}

					else {
						Patturn = LAttack_2;
						PaturnUpdate();
					}
				}
				else {
					if (dir == 1) {
						Patturn = LJump_2;
						PaturnUpdate();
					}
					else {
						Patturn = RJump_2;
						PaturnUpdate();
					}

				}


			}
		}
		break;

		case RJump_2: // 점프 준비 동작
			if (Time >= 0.4f) { // 애니메이션 끝남
				Patturn = RUpJump_2;
				PaturnUpdate();
			}
			else {
				jumpStartPos = getObjPos();
			}
			break;
		case RUpJump_2: // 점프 올라가는 중
		{
			Vec2 Pos1{};
			Pos1.x = jumpStartPos.x - Time / jumpDuration / 2 * 400 * dir;
			Pos1.y = jumpStartPos.y - sin(pie * Time / jumpDuration / 2) * 500;

			if (Pos1.x < 100.f || Pos1.x > 1180.f) {
				jumpStartPos.x = Pos1.x;
				dir *= -1;
				count += 1;
				getAnimator()->play(L"Lupjump_2");
			}

			setObjPos(Pos1);
			if (Time >= jumpDuration) { // 애니메이션 끝남
				jumpStartPos.x = Pos1.x;
				if (dir == 1) {
					Patturn = LDownJump_2;
					PaturnUpdate();
				}
				else {
					Patturn = RDownJump_2;
					PaturnUpdate();
				}
			}
		}
		break;

		case RDownJump_2: // 점프 내려가는 중
		{
			Vec2 Pos2{};
			Pos2.x = jumpStartPos.x - Time / jumpDuration / 2 * 400 * dir;
			Pos2.y = jumpStartPos.y - cos(pie * Time / jumpDuration / 2) * 500;

			if (Pos2.x < 100.f || Pos2.x > 1180.f) {
				jumpStartPos.x = Pos2.x;
				dir *= -1;
				count += 1;
				getAnimator()->play(L"Ldownjump_2");
			}

			setObjPos(Pos2);;
			if (Time >= jumpDuration) { // 애니메이션 끝남

				if (count == 3) {
					count = 0;
					if (dir == -1) {
						Patturn = RAttack_2;
						PaturnUpdate();
					}

					else {
						Patturn = LAttack_2;
						PaturnUpdate();
					}
				}
				else {

					if (dir == 1) {
						Patturn = LJump_2;
						PaturnUpdate();
					}
					else {
						Patturn = RJump_2;
						PaturnUpdate();
					}
				}

			}
		}
		break;

		case LAttack_2:
			if (Time >= 1.33f)
			{
				Patturn = LJump_2;
				PaturnUpdate();
			}
			break;

		case RAttack_2:
			if (Time >= 1.33f)
			{
				Patturn = RJump_2;
				PaturnUpdate();
			}
			break;
		}
	}
		break;
	case Phase3: 
	{

	}
		break;
	}
}



void Boss::PhaseTurn() {// 여기서 Phase 조건 걸면 됨

	if (KEY_TAP(InputData::P)) {
		Phase = Phase2;
		if (dir == -1) {
			Vec2 x = getObjPos();
			x.y = 500.f;
			setObjPos(x);
			Patturn = RPhaseTurn;
			PaturnUpdate();
		}
		else {
			Vec2 x = getObjPos();
			x.y = 500.f;
			setObjPos(x);
			Patturn = LPhaseTurn;
			PaturnUpdate();
		}

	}
}