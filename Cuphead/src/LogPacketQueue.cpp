#include "LogPacketQueue.hpp"

LogPacketQueue::LogPacketQueue( )
	: logPacketQueue_( ), queueMtx_( ), loginState_( LoginState::NONE ) {}

LogPacketQueue::~LogPacketQueue( ) {}

void LogPacketQueue::pushPacket( const Packet& packet ) {
	std::lock_guard<std::mutex> lock( queueMtx_ );
	logPacketQueue_.push( packet );
}

void LogPacketQueue::dispatch( ) {
	while ( !logPacketQueue_.empty( ) ) {
		std::lock_guard<std::mutex> lock( queueMtx_ );
		Packet p = logPacketQueue_.front( );
		logPacketQueue_.pop( );

		switch ( p.type ) {
		case PacketType::LOGIN_RESULT:
			loginState_ = p.lr.result ? LoginState::SUCCESS : LoginState::FAIL;
			break;
		}
	}
}