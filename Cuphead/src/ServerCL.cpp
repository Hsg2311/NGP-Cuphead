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
			// ������ ������ / �̸�
			retval = send(sock, (char*)&len, sizeof(int), 0);

			// ������ ������ (���� ����) / ��Ŷ ������
			retval = send(sock, (char*)&len, sizeof(int), 0);

			// ������ ������ (���� ����) / ��Ŷ
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
