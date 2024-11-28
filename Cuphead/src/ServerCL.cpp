#include "ServerCL.hpp"

using Clock = std::chrono::high_resolution_clock;
using Seconds = std::chrono::duration<float>;
inline constexpr Seconds operator""_s(unsigned long long _Val) noexcept {
	return Seconds(static_cast<float>(_Val));
}

ServerCL::ServerCL()
{
}

ServerCL::~ServerCL()
{
}



void ServerCL::clientRecv(SOCKET sock)
{
	while (1) {
		std::uint16_t bufferSize = 0;
		recv(sock, (char*)&bufferSize, sizeof(bufferSize), 0);

		auto buffer = std::array<char, BUFSIZE>();
		recv(sock, (char*)buffer.data(), bufferSize, 0);
	

		for (int readCnt = 0; readCnt < bufferSize / sizeof(ServerPacket); ++readCnt) {
			ServerPacket packet;
			std::copy(buffer.begin() + readCnt * sizeof(ServerPacket)
				, buffer.begin() + (readCnt + 1) * sizeof(ServerPacket)
				, reinterpret_cast<char*>(&packet));



			SendingStorage::getInst().pushPacket(packet);

		}



	}
}

void ServerCL::clientSend(SOCKET sock)
{
	static auto lastTp = Clock::now();
	while (1) {

		if (!SendingStorage::getInst().getFlag()) {
            
			auto tp = Clock::now();
			auto elapsedTime = std::chrono::duration_cast<Seconds>(tp - lastTp);
			lastTp = tp;

			if (elapsedTime < (1_s / 30.f)) {
				std::this_thread::sleep_for((1_s / 30.f) - elapsedTime);
			}
           
			auto buffer = std::array<char, BUFSIZE>();
            std::uint16_t bufferSize;
			SendingStorage::getInst().copyTo(buffer.data(), bufferSize);
			
			send(sock, (char*)&bufferSize, sizeof(bufferSize),0);
			send(sock, (char*)buffer.data(), bufferSize,0);

      
			SendingStorage::getInst().resetFlag();
		}
			
	}
}


