#include "PacketQueue.hpp"

std::mutex queueMutex;

void PacketQueue::pushPacket(const Packet& packet)
{
    std::lock_guard<std::mutex> lock(queueMutex);
	packetQueue.push(packet);
}

void PacketQueue::dispatch()
{
    while (!packetQueue.empty()) {
        Packet p;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            p = packetQueue.front();
            packetQueue.pop();
        }

        switch (p.type) {
        case PacketType::LOGIN: {

            break;
        }
        case PacketType::MOVE:

            break;
        }
    }
}

void PacketQueue::addObject(Object* obj)
{
    networkIDToObject[obj->getId()] = obj;
    objectToNetworkId[obj] = obj->getId();
}

void PacketQueue::deleteObject(Object* obj)
{
    networkIDToObject.erase(obj->getId());
    objectToNetworkId.erase(obj);

}
