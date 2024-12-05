#ifndef PACKETQUEUE_HPP
#define PACKETQUEUE_HPP

#include "protocol.hpp"
//#include "Object.hpp"

#include <queue>
#include <mutex>
#include <unordered_map>

class PacketQueue {
public:
	void pushPacket( const Packet& packet );
	void dispatch( );
	void addObject( Object* obj );
	void removeObject(std::uint16_t networkId);

	Object* getObject( std::uint16_t id ) {
		return networkIdToObject[ id ];
	}

private:
	std::queue<Packet> packetQueue_;
	std::mutex queueMtx_;

	std::unordered_map<uint16_t, Object*> networkIdToObject;
	std::unordered_map<Object*, uint16_t> objectToNetworkId;
};

#endif // PACKETQUEUE_HPP