#include "SlimeBoss.hpp"
#include "Timer.hpp"

SlimeBoss::SlimeBoss()
{
	Phase = Phase1;
	Patturn = LJump;

	SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::LJump);


}

void SlimeBoss::update()
{
	Time += Timer::getInst().getDT();

	TimeCheck();

	SendingStorage::getInst().pushPacket(Packet{
		.type = PacketType::MOVE,
		.rg = {
			.id = getID().value(),
			.groupType = GROUP_TYPE::ENEMY,
			.pos = getObjPos()
		}
	});
	
}

void SlimeBoss::onCollision(Object* other)
{
}

void SlimeBoss::onCollisionEntry(Object* other)
{
}

void SlimeBoss::onCollisionExit(Object* other)
{
}

void SlimeBoss::PaturnUpdate()
{
	//phase 1
	switch (Patturn) {
	case LJump:
		SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::LJump);
		break;
	case LUpJump:
		SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::LUpJump);
		break;
	case LDownJump:
		SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::LDownJump);
	
		break;
	case LAttack:
		SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::LAttack);
	
		break;

	case RJump:
		SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::RJump);
		
		break;
	case RUpJump:
		SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::RUpJump);
		
		break;
	case RDownJump:
		SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::RDownJump);
		break;
	case RAttack:
		SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::RAttack);
			
		break;
	}
}

void SlimeBoss::TimeCheck()
{
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
			Pos1.y = jumpStartPos.y - sin(3.14 * Time / jumpDuration / 2) * 300;

			if (Pos1.x < 100.f || Pos1.x > 1180.f) {
				jumpStartPos.x = Pos1.x;
				dir *= -1;
				count += 1;
				SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::RUpJump);
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
			Pos2.y = jumpStartPos.y - cos(3.14 * Time / jumpDuration / 2) * 300;

			if (Pos2.x < 100.f || Pos2.x > 1180.f) {
				jumpStartPos.x = Pos2.x;
				dir *= -1;
				count += 1;
				SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::RDownJump);
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
			Pos1.y = jumpStartPos.y - sin(3.14 * Time / jumpDuration / 2) * 300;

			if (Pos1.x < 100.f || Pos1.x > 1180.f) {
				jumpStartPos.x = Pos1.x;
				dir *= -1;
				count += 1;
				SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::LUpJump);
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
			Pos2.y = jumpStartPos.y - cos(3.14 * Time / jumpDuration / 2) * 300;

			if (Pos2.x < 100.f || Pos2.x > 1180.f) {
				jumpStartPos.x = Pos2.x;
				dir *= -1;
				count += 1;
				SendAnimPacket(PacketType::ANIMATION_RPC, AnimationRPC::Type::LDownJump);
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
	}

}

void SlimeBoss::SendAnimPacket(PacketType packet, AnimationRPC::Type type) {
	SendingStorage::getInst().pushPacket(Packet{
		.type = packet,
		.ar = {
			.id = getID().value(),
			.anim = type
			}
		});
}