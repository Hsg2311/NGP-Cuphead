#ifndef SENDING_STORAGE_HPP
#define SENDING_STORAGE_HPP

#include "define.hpp"
#include "protocol.hpp"

#include <atomic>
#include <array>
#include <mutex>
#include <cstdint>
#include <queue>

class SendingStorage {
	SINGLETON(SendingStorage);

public:
	void pushPacket(const Packet& packet);
	void copyTo(char* destBuffer, std::uint16_t& bufferSize);

	void setFlag() {
		flag_ = true;
	}

	void resetFlag() {
		flag_ = false;
	}

	bool getFlag() const {
		return flag_;
	}

	
private:
	std::atomic<bool> flag_;
	std::queue<Packet> packetQueue;
	std::queue<Packet> logPacketQueue;
	std::array<char, BUFSIZE> buffer_;
	std::uint16_t bufferSize_;
	std::mutex bufferMtx_;
};

// sender: buffer size
// sender: buffer data: [type, size, data][type, size, data]...

// receiver: buffer size
// receiver: buffer data: [type, size, data][type, size, data]...
// process packet: for (int readCnt = 0; readCnt < bufferSize / sizeof( Packet ); ++i) {
//						copy buffer[readCnt * sizeof( Packet )] to processed packet
// 						add processed packet to queue
//					}	

#endif // SENDING_STORAGE_HPP