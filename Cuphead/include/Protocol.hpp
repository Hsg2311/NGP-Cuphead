#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <iostream>

struct Player {
	int x, y;
	int hp;
	int entityId;
};

struct Boss {
	int x, y;
	int hp;
	int entityId;
};

enum class LogSystem : unsigned char {
	SignUp,
	LogIn,
	LogOut,

	CompletedSignUp,
	CompletedLogIn,
	CompletedLogOut,

	FailedSignUp,
	FailedLogIn,
	FailedLogOut,

	SaveLogfile
};

enum class ClientPacketType : unsigned char {
	Input = 3 //���Ƿ�...
};

enum class ServerPacketType : unsigned char {
	ClientStatePacket,
	EnemyStateUpdate,
	CollisionEvent,
	DeathEvent
};

struct SignUpOrLogInPacket {
	LogSystem type;
	std::string username;
	std::string password;
};

struct LogOutPacket {
	LogSystem type;
	std::string username;
};

struct InputPacket {
	unsigned char size;
	ClientPacketType type;
	unsigned char entityId;
	unsigned char dir;
	unsigned char jump;
	unsigned char attack;
};

struct ClientStatePacket {
	ServerPacketType type;
	short x, y;
	unsigned char hp;
};


struct EnemyStatePacket {
	ServerPacketType type;
	short x, y;
	unsigned char entityId;
	unsigned char hp;
};

struct CollisionEventPacket {
	ServerPacketType type;
	unsigned char entityId;
};

struct DeathEventPacket {
	ServerPacketType type;
	unsigned char entityId;
};

struct LoadSaveFile {
	ServerPacketType type;
	unsigned char stage;
};

#endif // PROTOCOL_HPP