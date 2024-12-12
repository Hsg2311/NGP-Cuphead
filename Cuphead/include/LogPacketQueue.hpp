#ifndef LOG_PACKET_QUEUE_HPP
#define LOG_PACKET_QUEUE_HPP

#include "define.hpp"
#include "protocol.hpp"

#include <queue>
#include <mutex>

class LogPacketQueue {
	SINGLETON( LogPacketQueue );

public:
	enum class LoginState {
		NONE,
		WAITING,
		SUCCESS,
		FAIL
	};

public:
	void pushPacket( const Packet& packet );
	void dispatch( );
	LoginState loginState( ) const { return loginState_; }
	void setLoginState( LoginState state ) { loginState_ = state; }

private:
	std::queue<Packet> logPacketQueue_;
	std::mutex queueMtx_;
	LoginState loginState_ = LoginState::NONE;
};

#endif // LOG_PACKET_QUEUE_HPP