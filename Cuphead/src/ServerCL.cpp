#include "ServerCL.hpp"



ServerCL::ServerCL()
{
}

ServerCL::~ServerCL()
{
}



void ServerCL::clientRecv(SOCKET sock)
{
	int retval;
	while (1) {
		
	}
}

void ServerCL::clientSend(SOCKET sock)
{
	int retval;
	static auto lastTp = Clock::now();
	while (1) {

		if (!SendingStorage::getInst().getFlag()) {
            
			auto tp = Clock::now();
			auto elapsedTime = std::chrono::duration_cast<Seconds>(tp - lastTp);
			lastTp = tp;

			if (elapsedTime < (1_s / 30.f)) {
				std::this_thread::sleep_for((1_s / 30.f) - elapsedTime);
			}
           
            char destBuffer[BUFSIZE] = { 0 }; 
            std::uint16_t bufferSize;

			send(sock, &bufferSize, sizeof(bufferSize));
			send(send, buffer.data(), bufferSize);

            SendingStorage::getInst().copyTo(destBuffer, bufferSize);

	

           


			SendingStorage::getInst().resetFlag();
		}
			
	}
}


void ServerCL::clientProcessPacket()
{
}

void ServerCL::processLogSystem()
{
}
