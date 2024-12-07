#include "BossScene.hpp"
#include "Background.hpp"
#include "Player.hpp"

#include "SendingStorage.hpp"

void BossScene::entry() {
	auto background = new Background(L"World Background", L"overworld/world1_large_island_main_01.png");
	background->setObjName(L"World Main Island");
	background->setObjPos(Vec2(640.f, 340.f));
	addObject(GROUP_TYPE::BACKGROUND, background);
	

	auto player = new Player();
	player->setObjName(L"Boss Player");
	player->setObjPos(Vec2(600.f, 800.f));
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
