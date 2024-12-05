#include <iostream>
#include <thread>
#include <fstream>

#include "Network.hpp"
#include "Protocol.hpp"
#include "Interface.hpp"

ServerPacket::Player players[2];
ServerPacket::Boss boss;

char buf[1024];

DWORD WINAPI sendThread(LPARAM sendSoket, void* sendBuf)
{
    SOCKET sock = static_cast<SOCKET>(sendSoket);

    // 소켓을 통해 패킷 전송
    int retval = send(sock, reinterpret_cast<char*>(sendBuf), sizeof(sendBuf), 0);
    if (retval == SOCKET_ERROR) {
        std::cerr << "Error sending packet." << std::endl;
    }
}

void sendClientState(int id)
{
    ServerPacket p;
    p.type = ServerPacketType::ClientStatePacket;

    p.clientState.hp = players[id].hp;
    p.clientState.x = players[id].x;
    p.clientState.y = players[id].y;
    
}

void sendEnemyState()
{
    ServerPacket p;
    p.type = ServerPacketType::EnemyStateUpdate;

    p.enemyState.hp = boss.hp;
    p.enemyState.x = boss.x;
    p.enemyState.y = boss.y;
    
}


void sendCollisionEvent(int id)
{
    ServerPacket p;
    p.type = ServerPacketType::CollisionEvent;

    p.collisionEvent.entityId = players[id].entityId;

}

void sendDeath(int id)
{
    ServerPacket p;
    p.type = ServerPacketType::DeathEvent;
    p.deathEvent.entityId = players[id].entityId;


}