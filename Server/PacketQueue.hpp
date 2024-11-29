#ifndef PACKETQUEUE_HPP
#define PACKETQUEUE_HPP

#include "protocol.hpp"
#include "Object.hpp"

#include <queue>
#include <mutex>
#include <unordered_map>

class PacketQueue {
public:
	void pushPacket( const Packet& packet );
	void dispatch( );
	void addObject( Object* obj );
	Object* getObject( std::uint16_t id ) {
		return networkIdToObject[ id ];
	}

	void processPacketQueue();
	
private:
	std::queue<Packet> packetQueue_;
	std::mutex queueMtx_;

	std::unordered_map<int, Object*> networkIdToObject;
	std::unordered_map<Object*, int> objectToNetworkId;
};

#endif // PACKETQUEUE_HPP