#include "ServerCL.hpp"
std::atomic_bool flag{ false };

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

		if (!flag) {
			flag = false;
			//getPacketInput()
			ClientPacket packet = Interface::getInst().getPacketInput();
			switch (packet.type) {
			case ClientPacketType::Input:
				
				break;
			case ClientPacketType::LogIn:

				break;
			case ClientPacketType::LogOut:

				break;
			}
		}
			
	}
}


void ServerCL::clientProcessPacket()
{
}

void ServerCL::processLogSystem()
{
}
