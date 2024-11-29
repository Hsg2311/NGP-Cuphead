#include "PacketQueue.hpp"
#include "Object.hpp"
#include "Timer.hpp"

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
		case PacketType::LOGIN:
			//handleLoginPacket( p );
			break;

		case PacketType::INPUT: 
			if (!getObject(p.mv.id)) {
				auto obj = new Object;
			}

			{
			auto lu = Vec2(-1.f, 1.f);
			auto ru = Vec2(1.f, 1.f);
			auto ld = Vec2(-1.f, -1.f);
			auto rd = Vec2(1.f, -1.f);

			lu.normalize();
			ru.normalize();
			ld.normalize();
			rd.normalize();

			bool bUp = p.in.up;
			bool bDown = p.in.down;
			bool bLeft = p.in.left;
			bool bRight = p.in.right;

			if (bUp && !bDown && !bLeft && !bRight) {
				objPos.y -= 300.f * Timer::getInst().getFDT();
			}
			if (bDown && !bUp && !bLeft && !bRight) {
				objPos.y += 300.f * Timer::getInst().getFDT();
			}
			if (bLeft && !bRight && !bUp && !bDown) {
				objPos.x -= 300.f * Timer::getInst().getFDT();
			}
			if (bRight && !bLeft && !bUp && !bDown) {
				objPos.x += 300.f * Timer::getInst().getFDT();
			}
			if (bLeft && bUp && !bDown && !bRight) {
				objPos.x -= 300.f * lu.x * Timer::getInst().getFDT();
				objPos.y -= 300.f * lu.y * Timer::getInst().getFDT();
			}
			if (bRight && bUp && !bDown && !bLeft) {
				objPos.x += 300.f * ru.x * Timer::getInst().getFDT();
				objPos.y -= 300.f * ru.y * Timer::getInst().getFDT();
			}
			if (bLeft && bDown && !bUp && !bRight) {
				objPos.x -= 300.f * ld.x * Timer::getInst().getFDT();
				objPos.y += 300.f * ld.y * Timer::getInst().getFDT();
			}
			if (bRight && bDown && !bUp && !bLeft) {
				objPos.x += 300.f * rd.x * Timer::getInst().getFDT();
				objPos.y += 300.f * rd.y * Timer::getInst().getFDT();
			}
			break;
		}
		}
	}
}

void PacketQueue::addObject(Object* obj) {
	networkIdToObject[obj->getNetworkId()] = obj;
	objectToNetworkId[obj] = obj->getNetworkId();
}