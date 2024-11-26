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
	while (1) {

		if (!flag.load()) {
			flag.store(false);
			Interface a;
			Interface::getData();
			// 데이터 보내기 / 이름
			retval = send(sock, (char*)&len, sizeof(int), 0);

			// 데이터 보내기 (고정 길이) / 패킷 사이즈
			retval = send(sock, (char*)&len, sizeof(int), 0);

			// 데이터 보내기 (가변 길이) / 패킷
			retval = send(sock, realFilename, len, 0);


		}
			
	}
}


void ServerCL::clientProcessPacket()
{
}

void ServerCL::processLogSystem()
{
}
