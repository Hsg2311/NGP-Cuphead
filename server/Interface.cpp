#include "Interface.hpp"

SendingStorage::SendingStorage(): flag_(false){}

void SendingStorage::pushPacket(const ServerPacket& packet)
{
	switch (packet.type) {
	case ServerPacketType::ClientStatePacket:{
		ServerPacket p;
		p.type = ServerPacketType::ClientStatePacket

		p.clientState.hp = players[id].hp;
		p.clientState.x = players[id].x;
		p.clientState.y = players[id].y;
		break;
	}

	case ServerPacketType::EnemyStateUpdate:{
		ServerPacket p;
		p.type = ServerPacketType::EnemyStateUpdate;
		
		p.enemyState.hp = boss.hp;
		p.enemyState.x = boss.x;
		p.enemyState.y = boss.y;
		break;
	}

	case ServerPacketType::CollisionEvent:{
		ServerPacket p;
		p.type = ServerPacketType::CollisionEvent;

		p.collisionEvent.entityId = players[id].entityId;

		break;
	}

	case ServerPacketType::DeathEvent:{
		ServerPacket p;
		p.type = ServerPacketType::DeathEvent;
		p.deathEvent.entityId = players[id].entityId;
		break;
	}
	case ServerPacketType::CompletedSignUp: {

		break;
	}

	case ServerPacketType::CompletedLogIn: {

		break;
	}

	case ServerPacketType::CompletedLogOut: {

		break;
	}


	case ServerPacketType::FailedSignUp: {

		break;
	}

	case ServerPacketType::FailedLogIn: {

		break;
	}

	case ServerPacketType::FailedLogOut: {

		break;
	}


	case  ServerPacketType::SaveLogfile: {

		break;
	}
	}
}

void SendingStorage::setFlag()
{

	flag_ = true;
}

void SendingStorage::resetFlag()
{
	flag_ = false;
}

void SendingStorage::copyTo(char* destBuffer)
{
	{
		std::lock_guard<std::mutex>lock(bufferMtx_);
		std::memcpy(destBuffer, &buffer_, sizeof(buffer_));
	}
}
