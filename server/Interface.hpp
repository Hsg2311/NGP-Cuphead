#include <iostream>
#include <mutex>
#include "Network.hpp"

class SendingStorage {
public:
	Singleton();

	void pushPacket(const ServerPacket& packet);
	void setFlag();
	void resetFlag();
	void copyTo(char* destBuffer);  //->이 안에서 lock과 unlock

private:
	std::atomic<bool> flag_;
	char buffer_[BUFSIZE];
	std::mutex bufferMtx_;
}