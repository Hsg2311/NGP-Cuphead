#include "BossScene.hpp"
#include "Background.hpp"
#include "Player.hpp"

#include "SendingStorage.hpp"

#include "Boss.hpp"

void BossScene::entry() {

	auto background = new Background(L"World Background", L"smile_boss/slime_background.png");
	background->setObjName(L"World Boss background");
	background->setObjPos(Vec2(640.f, 360.f));
	addObject(GROUP_TYPE::BACKGROUND, background);

	auto boss = new Boss();
	boss->setObjName(L"World Boss");
	boss->setObjPos(Vec2(1000.f, 500.f));
	addObject(GROUP_TYPE::ENEMY, boss);
	sendRegisterPacket(ObjectName::Boss, boss->getNetworkId());
	PacketQueue::getInst().addObject(boss, ObjectName::Boss);



	auto player = new Player();
	player->setObjName(L"Boss Player");
	player->setObjPos(Vec2(600.f, 500.f));
	addObject(GROUP_TYPE::PLAYER, player);
	sendRegisterPacket(ObjectName::BossPlayer, player->getNetworkId());
	PacketQueue::getInst().addObject(player, ObjectName::BossPlayer);

}

void BossScene::sendRegisterPacket(ObjectName objectname, std::uint16_t id)
{
	auto registerPacket = Packet{
		.type = PacketType::REGISTER,
		.rs = {
			.objectname = objectname,
			.state = MapManage::ADD,
			.id = id
		}
	};

	SendingStorage::getInst().pushPacket(registerPacket);
}
