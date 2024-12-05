#include "LogPacketQueue.hpp"
#include "SendingStorage.hpp"


char ID[ 16 ] = "test ID";
char PW[ 16 ] = "test PW";

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
		case PacketType::LOGIN: {
			strcmp( p.lg.id, ID ) == 0 && strcmp( p.lg.pw, PW ) == 0 ?
				loginState_ = LoginState::SUCCESS : loginState_ = LoginState::FAIL;
		
			auto packet = Packet{
				.type = PacketType::LOGIN_RESULT,
				.lr = {
					.result = loginState_ == LoginState::SUCCESS ? true : false
				}
			};

			SendingStorage::getInst( ).pushPacket( packet );
			break;
		}
		}
	}
}