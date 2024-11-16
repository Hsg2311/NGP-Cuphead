#include <iostream>
#include <thread>

#include "Network.hpp"
#include "Protocol.hpp"

char buf[1024];
Player players[2];

void processPacket(int id, char* packet)
{
	InputPacket* pk = reinterpret_cast<InputPacket*>(packet);

	players[pk->entityId].x
	

}

DWORD WINAPI recvThread(LPARAM lparam)
{
	while (true) {
		int retval = recv(sock_, buf, sizeof(buf), 0);

		processPacket();
	}


}
