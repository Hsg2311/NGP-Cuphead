#include <iostream>
#include <thread>

#include "Network.hpp"
#include "Protocol.hpp"

char buf[1024];
Player players[2];

void processPacket(char* buf)
{
	unsigned char packetType = static_cast<unsigned char>(buf[0]);

	switch (packetType) {
	case static_cast<unsigned char>(ClientPacketType::Input): {
		InputPacket* pk = reinterpret_cast<InputPacket*>(buf);

		int clientId = pk->entityId;

		players[clientId].x += pk->dir;
		players[clientId].y += pk->dir;

		recvQueue.push(players[clientId]);
		break;
	}

	case static_cast<unsigned char>(LogSystem::SignUp): {
		SignUpOrLogInPacket* signUpPacket = reinterpret_cast<SignUpOrLogInPacket*>(buf);

		break;
	}
	case static_cast<unsigned char>(LogSystem::LogIn): {
		SignUpOrLogInPacket* signUpPacket = reinterpret_cast<SignUpOrLogInPacket*>(buf);

		break;
	}
	case static_cast<unsigned char>(LogSystem::LogOut): {
		LogOutPacket* signUpPacket = reinterpret_cast<LogOutPacket*>(buf);


		break;
	}

	default:

		break;
	}

}

DWORD WINAPI recvThread(LPARAM sock_)
{
	while (true) {
		int retval = recv(sock_, buf, sizeof(buf), 0);

		processPacket(buf);
	}


}
