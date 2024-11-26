#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

#include "Network.hpp"
#include "Protocol.hpp"


//Player players[2];


void processPacket(ClientPacketType type, char* buf, int bufSize)
{
	ClientPacket packet;
	switch (type) {
	case ClientPacketType::Input:
	{

		ClientPacket::InputPacket* p = reinterpret_cast<ClientPacket::InputPacket*>(buf);
		packet.input = *p;

		{
			std::lock_guard<std::mutex>lock(queueMutex);
			recvQueue.push(packet);
		}
		break;
	}

	case ClientPacketType::LogIn: {
		ClientPacket::SignUpOrLogInPacket* p = reinterpret_cast<ClientPacket::SignUpOrLogInPacket*>(buf);

		packet.signUp = *p; // union의 SignUpOrLogInPacket에 복사

		{
			std::lock_guard<std::mutex> lock(queueMutex);
			recvQueue.push(packet);
		}
		break;
	}

	case ClientPacketType::LogOut: {
		ClientPacket::LogOutPacket* p = reinterpret_cast<ClientPacket::LogOutPacket*>(buf);

		packet.logOut = *p; // union의 SignUpOrLogInPacket에 복사

		{
			std::lock_guard<std::mutex> lock(queueMutex);
			recvQueue.push(packet);
		}
		break;
	}
	}
}

DWORD WINAPI recvThread(LPARAM sock_)
{
	SOCKET sock = static_cast<SOCKET>(sock_);
	//패킷타입, 패킷 사이즈, 데이터

	ClientPacketType type;
	int retval = recv(sock_, (char*)&type, sizeof(type), 0);
	if (retval == SOCKET_ERROR) {
		std::cerr << "type_recv_error " << WSAGetLastError() << std::endl;
	}

	short packSize;
	retval = recv(sock_, (char*)packSize, sizeof(packSize), 0);
	if (retval == SOCKET_ERROR) {
		std::cerr << "packet_recv_error " << WSAGetLastError() << std::endl;
	}

	char buf[512];

	retval = recv(sock_, (char*)buf, packSize, 0);
	if (retval == SOCKET_ERROR) {
		std::cerr << "packet_recv_error " << WSAGetLastError() << std::endl;
	}

	processPacket(type, buf, packSize);
}