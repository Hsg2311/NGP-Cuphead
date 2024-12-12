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
	void flush( char* destBuffer, std::uint16_t& bufferSize );

	void setFlag( ) {
		flag_ = true;
	}

	void resetFlag( ) {
		flag_ = false;
	}

	bool getFlag( ) const {
		return flag_;
	}

private:
	std::atomic<bool> flag_;

	std::array<char, BUFSIZE> buffer_;
	std::uint16_t bufferSize_;
	std::mutex bufferMtx_;
};

#endif	// SENDING_STORAGE_HPP