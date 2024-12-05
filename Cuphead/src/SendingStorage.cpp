
#include "SendingStorage.hpp"

#include <algorithm>
#include <cassert>
#include <limits>

SendingStorage::SendingStorage( )
	: flag_( false ), buffer_( ), bufferSize_( 0 ), bufferMtx_( ) {}

SendingStorage::~SendingStorage( ) {}

void SendingStorage::pushPacket( const Packet& packet ) {
	auto lock = std::lock_guard( bufferMtx_ );

	std::copy( reinterpret_cast<const char*>( &packet )
		, reinterpret_cast<const char*>( &packet ) + sizeof( packet )
		, buffer_.begin( ) + bufferSize_ );

	assert( bufferSize_ < bufferSize_ + sizeof( packet ) );		// �����÷ο� ����
	bufferSize_ += sizeof( packet );

	setFlag( );	// ��Ŷ�� �������� flag�� true��
	// bufferSize_(offset) �Ѿ�� ��Ŷ ó���ؾ� �� -> ������ ������
}

void SendingStorage::flush( char* destBuffer, std::uint16_t& bufferSize ) {
	auto lock = std::lock_guard( bufferMtx_ );
	std::copy( buffer_.begin( ), buffer_.end( ), destBuffer );
	bufferSize = bufferSize_;

	buffer_.fill( 0 );
	bufferSize_ = 0;
}

