#include <iostream>
#include <thread>
#include <fstream>

#include "Network.hpp"
#include "Protocol.hpp"

char buf[1024];

DWORD WINAPI sendThread(LPARAM sendSoket, void* sendBuf)
{
    SOCKET sock = static_cast<SOCKET>(sendSoket);

   /* ServerPacketType packetType = *reinterpret_cast<ServerPacketType*>(sendSoket);

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
    }*/

    // 소켓을 통해 패킷 전송
    int retval = send(sock, reinterpret_cast<char*>(sendBuf), sizeof(sendBuf), 0);
    if (retval == SOCKET_ERROR) {
        std::cerr << "Error sending packet." << std::endl;
    }
}

void sendClientState(int id)
{
    ClientStatePacket p;
    p.hp = players[id].hp;
    p.type = ServerPacketType::ClientStatePacket;
    p.x = players[id].x;
    p.y = players[id].y;
    
}

void sendEnemyState()
{
    EnemyStatePacket p;
    //p.entityId
    p.hp = boss.hp;
    p.type = ServerPacketType::EnemyStateUpdate;
    p.x = boss.x;
    p.y = boss.y;
}


void sendCollisionEvent(int id)
{
    CollisionEventPacket p;
    p.entityId = players[id].entityId;
    p.type = ServerPacketType::CollisionEvent;
}

void sendDeath(int id)
{
    DeathEventPacket p;
    p.entityId = players[id].entityId;
    p.type = ServerPacketType::DeathEvent;


}