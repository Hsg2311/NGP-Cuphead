#ifndef SENDING_STORAGE_HPP
#define SENDING_STORAGE_HPP

#include "define.hpp"
#include "protocol.hpp"

#include <atomic>
#include <array>
#include <mutex>
#include <cstdint>

class SendingStorage {
	SINGLETON( SendingStorage );

public:
	void pushPacket( const Packet& packet );

	void setFlag( ) {
		flag_ = true;
	}

	void resetFlag( ) {
		flag_ = false;
	}

	void copyTo( char* destBuffer );

private:
	std::atomic<bool> flag_;

	std::array<char, BUFSIZE> buffer_;
	std::uint16_t offset_;
	std::mutex bufferMtx_;
};

#endif // SENDING_STORAGE_HPP