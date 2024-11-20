#include <iostream>
#include <thread>
#include <vector>
#include "Network.hpp"
#include "Protocol.hpp"

std::vector<char> recvBuf;
Player players[2];

void processPacket(char* buf)
{
	InputPacket* packet = reinterpret_cast<InputPacket*>(buf);


}

DWORD WINAPI recvThread(LPARAM sock_)
{
	char tempBuf[1024];

	while (true) {
		int retval = recv(sock_, tempBuf, sizeof(tempBuf), 0);
		if (retval > 0) {
			recvBuf.insert(recvBuf.end(), tempBuf, tempBuf + retval);

			while (recvBuf.size() >= sizeof(InputPacket)) {
				processPacket(recvBuf.data());
				recvBuf.erase(recvBuf.begin(), recvBuf.begin() + sizeof(InputPacket));
			}
		}
		else if (retval == 0) {
			std::cout << "Connection closed" << std::endl;
			break;
		}
		else {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK) {
				continue;
			}
			std::cerr << "recv error: " << err << std::endl;
			break;
		}
	}
	return 0;
}
