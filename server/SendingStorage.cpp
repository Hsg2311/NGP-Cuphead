#include "SendingStorage.hpp"

#include <algorithm>

SendingStorage::SendingStorage( )
	: flag_( false ), buffer_( ), offset_( 0 ), bufferMtx_( ) {}

SendingStorage::~SendingStorage( ) {}

void SendingStorage::pushPacket( const Packet& packet ) {
	std::copy( reinterpret_cast<const char*>( &packet )
		, reinterpret_cast<const char*>( &packet ) + sizeof( packet )
		, buffer_.begin( ) + offset_ );

	offset_ += sizeof( packet );
}

void SendingStorage::copyTo( char* destBuffer ) {
	auto lock = std::lock_guard<std::mutex>( bufferMtx_ );
	std::copy( buffer_.begin( ), buffer_.end( ), destBuffer );
}