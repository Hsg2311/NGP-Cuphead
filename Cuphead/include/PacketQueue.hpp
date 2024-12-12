#ifndef PACKETQUEUE_HPP
#define PACKETQUEUE_HPP

#include "define.hpp"
#include "protocol.hpp"
#include "Object.hpp"

#include <queue>
#include <mutex>
#include <unordered_map>

class PacketQueue {
	SINGLETON( PacketQueue );

public:
	void pushPacket( const Packet& packet );
	void dispatch( );

	void addObject( Object* obj ) {
		networkIdToObject_[ obj->getID( ).value( ) ] = obj;
		objectToNetworkId_[ obj ] = obj->getID( ).value( );
	}

	Object* getObject( std::uint16_t id ) {
		return networkIdToObject_[ id ];
	}

	bool hasId( std::uint16_t id ) const {
		return networkIdToObject_.contains( id );
	}

	void removeObject( Object* obj ) {
		networkIdToObject_.erase( objectToNetworkId_[ obj ] );
		objectToNetworkId_.erase( obj );
	}

private:
	std::queue<Packet> packetQueue_;
	std::mutex queueMtx_;

	std::unordered_map<int, Object*> networkIdToObject_;
	std::unordered_map<Object*, int> objectToNetworkId_;
};

#endif // PACKETQUEUE_HPP