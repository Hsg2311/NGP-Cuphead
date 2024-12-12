#include "SlimeScene.hpp"
#include "Background.hpp"
#include "Player.hpp"
#include "PacketQueue.hpp"

#include "SlimeBoss.hpp"

void SlimeScene::entry() {
	auto background = new Background(L"Slime Background", L"smile_boss/slime_background.png");
	background->setObjName(L"Slime Background");
	background->setObjPos(Vec2(640.f, 340.f));
	addObject(GROUP_TYPE::BACKGROUND, background);
}

void SlimeScene::handlePacket(const Packet& packet) {
	switch (packet.type) {
	case PacketType::REGISTER:
		handleRegisterPacket(packet);
		break;

	case PacketType::DESTROY:
		break;

	case PacketType::MOVE:
		handleMovePacket(packet);
		break;

	default: break;
	}
}

void SlimeScene::handleRegisterPacket(const Packet& packet) {
	auto info2 = std::vector<texInfo>();
	info2.push_back(texInfo{
		.resKey = L"L_run",
		.fileName = L"Lrun.png",
		.sliceSize = Vec2(150.f, 170.f),
		.duration = 0.11f,
		.frameCount = 16,
		});
	info2.push_back(texInfo{
		.resKey = L"R_run",
		.fileName = L"Rrun.png",
		.sliceSize = Vec2(150.f, 170.f),
		.duration = 0.11f,
		.frameCount = 16
		});
	info2.push_back(texInfo{
		.resKey = L"L_Idle",
		.fileName = L"cuphead_idle.png",
		.sliceSize = Vec2(100.f, 155.f),
		.duration = 0.11f,
		.frameCount = 9
		});

	info2.push_back(texInfo{
		.resKey = L"L_Jump",
		.fileName = L"cuphead_idle.png",
		.sliceSize = Vec2(100.f, 155.f),
		.duration = 0.11f,
		.frameCount = 9
		});

	info2.push_back(texInfo{
		.resKey = L"R_Jump",
		.fileName = L"cuphead_idle.png",
		.sliceSize = Vec2(100.f, 155.f),
		.duration = 0.11f,
		.frameCount = 9
		});


	auto player = new Player(info2);
	player->setObjPos(packet.rg.pos);
	player->setID(packet.rg.id);

	if (packet.rg.groupType == GROUP_TYPE::CUPHEAD) {
		if (gImCuphead) {
			player->setInputEnabled(true);
		}
		player->setObjName(L"Cuphead Player");
		addObject(GROUP_TYPE::CUPHEAD, player);
	}
	else if (packet.rg.groupType == GROUP_TYPE::MUGMAN) {
		if (!gImCuphead) {
			player->setInputEnabled(true);
		}
		player->setObjName(L"Mugman Player");
		addObject(GROUP_TYPE::MUGMAN, player);
	}


	auto boss = new SlimeBoss();
	boss->setObjName(L"World Boss");
	boss->setID(packet.rg.id);
	boss->setObjPos(packet.rg.pos);
	addObject(GROUP_TYPE::ENEMY, boss);	


	PacketQueue::getInst().addObject(player);
}

void SlimeScene::handleDestroyPacket(const Packet& packet) {
}

void SlimeScene::handleMovePacket(const Packet& packet) {
	auto obj = PacketQueue::getInst().getObject(packet.mv.id);
	obj->setObjPos(packet.mv.pos);
}

void SlimeScene::handleAnimationRPCPacket(const Packet& packet)
{
	auto obj = PacketQueue::getInst().getObject(packet.ar.id);

	switch (packet.ar.anim)
	{
	case AnimationRPC::Type::LJump:
		obj->getAnimator()->play(L"Ljump");
		break;

	case AnimationRPC::Type::LUpJump:
		obj->getAnimator()->play(L"Lupjump");
		break;

	case AnimationRPC::Type::LDownJump:
		obj->getAnimator()->play(L"Ldownjump");
		break;

	case AnimationRPC::Type::LAttack:
		obj->getAnimator()->play(L"LAttack");
		break;

	case AnimationRPC::Type::RJump:
		obj->getAnimator()->play(L"Rjump");
		break;

	case AnimationRPC::Type::RUpJump:
		obj->getAnimator()->play(L"Rupjump");
		break;

	case AnimationRPC::Type::RDownJump:
		obj->getAnimator()->play(L"Rdownjump");
		break;

	case AnimationRPC::Type::RAttack:
		obj->getAnimator()->play(L"RAttack");
		break;

	default:
		break;
	}
}