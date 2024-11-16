#include "Network.hpp"
#include <queue>
#include "Protocol.hpp"
#include <iostream>

std::queue<std::string> recvQueue;
char buffer[1024];

namespace network {

	void network::initNet( ) {
	}

	void network::closeNet( ) {
	}

	Exception::Exception( int line, const char* file, int error, std::string_view desc ) NET_NOEXCEPT
		: MyException( line, file ), error_( error ) {
	}
}

void processPacket(int id, char* packet, int packetSize)
{

	ServerPacketType packetType = static_cast<ServerPacketType>(packet[0]);

	switch (packetType) {
    case ServerPacketType::PlayerStateUpdate:
        std::cout << "PlayerStateUpdate " << id << std::endl;
        break;

    case ServerPacketType::EnemyStateUpdate:
        std::cout << "EnemyStateUpdate" << id << std::endl;
        break;

    case ServerPacketType::CollisionEvent:
        std::cout << "CollisionEvent " << id << std::endl;
        break;

    case ServerPacketType::DeathEvent:
        std::cout << "DeathEvent " << id << std::endl;
        break;

    default:
        std::cout << "Unknown packet" << std::endl;
        break;
	}
}

void recvThread()
{
	while(true) {
		int retval = recv(socket, buffer, sizeof(buffer), 0);

		processPacket( )
	}

	

}
