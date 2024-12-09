#include "PacketQueue.hpp"
#include "Timer.hpp"
#include "Object.hpp"
#include "SendingStorage.hpp"

void PacketQueue::pushPacket(const Packet& packet) {
	std::lock_guard<std::mutex> lock(queueMtx_);
	packetQueue_.push(packet);
}

void PacketQueue::dispatch() {
	while (!packetQueue_.empty()) {
		std::lock_guard<std::mutex> lock(queueMtx_);
		Packet p = packetQueue_.front();
		packetQueue_.pop();

		switch (p.type) {
		case PacketType::INPUT: {
			/*auto lu = Vec2( -1.f, 1.f );
			auto ru = Vec2( 1.f, 1.f );
			auto ld = Vec2( -1.f, -1.f );
			auto rd = Vec2( 1.f, -1.f );

			lu.normalize( );
			ru.normalize( );
			ld.normalize( );
			rd.normalize( );

			bool bUp = p.in.up;
			bool bDown = p.in.down;
			bool bLeft = p.in.left;
			bool bRight = p.in.right;

			if ( bUp && !bDown && !bLeft && !bRight ) {
				objPos.y -= 300.f * Timer::getInst( ).getFDT( );
			}
			if ( bDown && !bUp && !bLeft && !bRight ) {
				objPos.y += 300.f * Timer::getInst( ).getFDT( );
			}
			if ( bLeft && !bRight && !bUp && !bDown ) {
				objPos.x -= 300.f * Timer::getInst( ).getFDT( );
			}
			if ( bRight && !bLeft && !bUp && !bDown ) {
				objPos.x += 300.f * Timer::getInst( ).getFDT( );
			}
			if ( bLeft && bUp && !bDown && !bRight ) {
				objPos.x -= 300.f * lu.x * Timer::getInst( ).getFDT( );
				objPos.y -= 300.f * lu.y * Timer::getInst( ).getFDT( );
			}
			if ( bRight && bUp && !bDown && !bLeft ) {
				objPos.x += 300.f * ru.x * Timer::getInst( ).getFDT( );
				objPos.y -= 300.f * ru.y * Timer::getInst( ).getFDT( );
			}
			if ( bLeft && bDown && !bUp && !bRight ) {
				objPos.x -= 300.f * ld.x * Timer::getInst( ).getFDT( );
				objPos.y += 300.f * ld.y * Timer::getInst( ).getFDT( );
			}
			if ( bRight && bDown && !bUp && !bLeft ) {
				objPos.x += 300.f * rd.x * Timer::getInst( ).getFDT( );
				objPos.y += 300.f * rd.y * Timer::getInst( ).getFDT( );
			}*/
			break;
		}
		case PacketType::REGISTER: {
			switch (p.rs.objecType) {
			case ObjectType::OverworldPlayer: {
				Object* obj = new Object();
				obj->setId(p.rs.id);
				obj->setPosition(/*where*/Vec2());

				if (p.rs.state == MapManage::ADD) {
					addObject(obj);
					auto packet = Packet{
						.type = PacketType::MOVE,
						.mv = {
							.id = obj->getNetworkId(),
							.dir = Direction::NONE,
							.pos = obj->getPosition()
}
					};
					SendingStorage::getInst().pushPacket(packet);
				}

				else if (p.rs.state == MapManage::REMOVE) {
					removeObject(obj->getNetworkId()/*p.rs.id*/);

				}

				break;
			}
			case ObjectType::StagePlayer: {

			}
			}
		}
		}
	}
}

void PacketQueue::addObject(Object* obj) {
	networkIdToObject[obj->getNetworkId()] = obj;
	objectToNetworkId[obj] = obj->getNetworkId();
}

void PacketQueue::removeObject(std::uint16_t networkId)
{
	auto it = networkIdToObject.find(networkId);
	if (it != networkIdToObject.end()) {
		Object* obj = it->second;
		objectToNetworkId.erase(obj);
		networkIdToObject.erase(it);
		delete obj;
	}
}
