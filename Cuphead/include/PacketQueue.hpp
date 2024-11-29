#include "Protocol.hpp"
#include "Scene.hpp"
#include <queue>
#include <unordered_map>
#include <mutex>



extern std::mutex queueMutex;

class Object;

class PacketQueue {

    SINGLETON(PacketQueue);

public:
    void pushPacket(const Packet& packet);
    void dispatch();
    void addObject(Object* obj);
    void deleteObject(Object* obj);
    Object* getObject(std::uint8_t id) {
        return networkIDToObject[id];
    }

private:
    std::queue<Packet> packetQueue;
    std::mutex queueMtx_;

    std::unordered_map<uint8_t, Object*> networkIDToObject;
    std::unordered_map<Object*, uint8_t> objectToNetworkId;
};