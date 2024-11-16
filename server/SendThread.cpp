#include <iostream>
#include <thread>

#include "Network.hpp"
#include "Protocol.hpp"

char buf[1024];

DWORD WINAPI sendThread(LPARAM lparam)
{
    ServerPacketType packetType = *reinterpret_cast<ServerPacketType*>(lparam);

    switch (packetType) {
    case ServerPacketType::ClientStatePacket: {
        ClientStatePacket playerPacket{ ServerPacketType::ClientStatePacket, 100, 100, 100};
        memcpy(buf, &playerPacket, sizeof(playerPacket)); 
        break;
    }
    case ServerPacketType::EnemyStateUpdate: {

        EnemyStatePacket enemyPacket{ ServerPacketType::EnemyStateUpdate, 100, 100, 1, 100 };
        memcpy(buf, &enemyPacket, sizeof(enemyPacket)); 
        break;
    }
    case ServerPacketType::CollisionEvent: {

        CollisionEventPacket collisionPacket{ ServerPacketType::CollisionEvent, 1 };
        memcpy(buf, &collisionPacket, sizeof(collisionPacket));
        break;
    }
    case ServerPacketType::DeathEvent: {
    
        DeathEventPacket deathPacket{ ServerPacketType::DeathEvent, 1 };
        memcpy(buf, &deathPacket, sizeof(deathPacket)); 
        break;
    }
    default:
        std::cerr << "Unknown packet" << std::endl;
        return 0;
    }

    // 소켓을 통해 패킷 전송
    int retval = send(sock_, buf, sizeof(buf), 0);
    if (retval == SOCKET_ERROR) {
        std::cerr << "Error sending packet." << std::endl;
    }
}