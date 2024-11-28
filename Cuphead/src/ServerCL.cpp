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

		if (!SendingStorage::getInst().getFlag()) {
            SendingStorage::getInst().resetFlag();

           
            char destBuffer[BUFSIZE] = { 0 }; 
            std::uint16_t bufferSize;

      
            SendingStorage::getInst().copyTo(destBuffer, bufferSize);

 
            ClientPacket packet;
            std::memcpy(&packet, destBuffer, sizeof(ClientPacket));
            
            retval = send(sock, (char*)&packet.type, sizeof(ClientPacketType), 0);

            // 패킷 처리
            switch (packet.type) {
            case ClientPacketType::Input:
                auto packetSize = sizeof(ClientPacketType) + sizeof(packet.Input);

                retval = send(sock, (char*)&packetSize, sizeof(packetSize), 0);
                
                retval = send(sock, (char*)&packet.Input, sizeof(packet.Input), 0);
                break;

            case ClientPacketType::LogIn:
                auto packetSize = sizeof(ClientPacketType) + sizeof(packet.LogIn);

                retval = send(sock, (char*)&packetSize, sizeof(packetSize), 0);

                retval = send(sock, (char*)&packet.LogIn, sizeof(packet.LogIn), 0);
               
                break;

            case ClientPacketType::LogOut:
                auto packetSize = sizeof(ClientPacketType) + sizeof(packet.LogOut);

                retval = send(sock, (char*)&packetSize, sizeof(packetSize), 0);

                retval = send(sock, (char*)&packet.LogOut, sizeof(packet.LogOut), 0);
               
                break;

            default:
                
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
