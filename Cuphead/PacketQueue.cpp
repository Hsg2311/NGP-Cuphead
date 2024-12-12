#include "PacketQueue.hpp"
#include "SceneHandler.hpp"

PacketQueue::PacketQueue( )
	: packetQueue_( ), queueMtx_( ), networkIdToObject_( ), objectToNetworkId_( ) {}

PacketQueue::~PacketQueue( ) {}

void PacketQueue::pushPacket( const Packet& packet ) {
	std::lock_guard<std::mutex> lock( queueMtx_ );
	packetQueue_.push( packet );
}

void PacketQueue::dispatch( ) {
	while ( !packetQueue_.empty( ) ) {
		std::lock_guard<std::mutex> lock( queueMtx_ );
		Packet p = packetQueue_.front( );
		packetQueue_.pop( );

		SceneHandler::getInst( ).getCurrScene( )->handlePacket( p );
	}
}

