#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <iostream>
#include <atomic>

#define BUFSIZE 1024

std::atomic_bool flag{false};

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



enum class ServerPacketType : unsigned char {
	ClientStatePacket,
	EnemyStateUpdate,
	CollisionEvent,
	DeathEvent
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

enum class ClientPacketType : unsigned char {
	Input = 3 //¿”¿«∑Œ...
};

struct InputPacket {
	ClientPacketType type;
	unsigned char entityId;
	unsigned char dir;
	unsigned char jump;
	unsigned char attack;
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

#endif // PROTOCOL_HPP