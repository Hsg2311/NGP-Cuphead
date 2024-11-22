#include <iostream>
#include <thread>
#include <vector>
#include "Network.hpp"
#include "Protocol.hpp"

char buf[512];
Player players[2];

void processPacket(char* buf, int bufSize)
{
    unsigned char type = buf[0]; // 패킷의 첫 바이트를 타입으로 간주

    if (bufSize >= sizeof(InputPacket)) { 
        InputPacket* inputPacket = reinterpret_cast<InputPacket*>(buf);
        recvQueue.push(inputPacket);
    }
    else { // LogSystem 처리
        LogSystem logType = static_cast<LogSystem>(type);

        if (logType == LogSystem::SignUp) {
            std::cout << "SignUp Packet received\n";
           
        }
        else if (logType == LogSystem::LogIn) {
            std::cout << "LogIn Packet received\n";
          
        }
        else if (logType == LogSystem::LogOut) {
            std::cout << "LogOut Packet received\n";
           
        }
    }
}

DWORD WINAPI recvThread(LPARAM sock_)
{
    SOCKET sock = static_cast<SOCKET>(sock_);

	int fileSize;
	int retval = recv(sock_, (char*)&fileSize, sizeof(fileSize), 0);
	if (retval == SOCKET_ERROR) {
		std::cerr << "size_recv_error " << WSAGetLastError() << std::endl;
	}

	int retval = recv(sock_, buf, fileSize, 0);
	if (retval == SOCKET_ERROR) {
		std::cerr << "packet_recv_error " << WSAGetLastError() << std::endl;
	}
	processPacket(buf, fileSize);
	return 0;
}
