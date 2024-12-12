#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "struct.hpp"
#include "define.hpp"

#include <cstdint>

constexpr short PORT = 9000;
constexpr short BUFSIZE = 1024;

extern bool gCupheadLogin;
extern bool gMugmanLogin;

extern bool gImCuphead;

enum class PacketType {
	NONE,

	LOGIN,
	LOGIN_RESULT,
	LEAVE,

	REPLICATION,
	REGISTER,
	DESTROY,
	MOVE,
	INPUT,
	TRY_GAME_START,
	LOGOUT,
	CHANGE_SCENE,
	CHANGE_SCENE_ACK,
};

enum class Direction {
	NONE,

	E, W, S, N,
	NE, NW, SE, SW,
};

struct LoginPacket {	// client -> server
	char id[ 16 ];
	char pw[ 16 ];
};

struct LoginResultPacket {	// server -> client
	bool result;
	bool cupheadLogin;
	bool mugmanLogin;

	enum class Type {
		None,
		Cuphead,
		Mugman
	};
	Type who;
};

struct RegisterPacket {	// server -> client
	std::uint16_t id;

	/*
	특정 타입
	해당 타입을 초기화하는데 필요한 모든 인자
	*/
	GROUP_TYPE groupType;
	Vec2 pos;
};

struct MovePacket {	// server -> client
	std::uint16_t id;
	Direction dir;
	Vec2 pos;
};

struct InputPacket {	// client -> server
	std::uint16_t id;
	bool left, right, up, down;
};

// Animation Remote Procedure Call
struct AnimationRPC {	// server -> client
	enum class Type {
		IdleRight
	};

	std::uint16_t id;
	Type anim;
};

struct DestroyPacket {	// server -> client
	std::uint16_t id;
};

// struct TryGameStartPacket {};

struct ChangeScenePacket {
	SCENE_TYPE scene;
};

struct ChangeSceneAckPacket {
	bool imCuphead;
};

struct LeavePacket {
	bool imCuphead;
};

struct LogoutPacket {
	bool imCuphead;
};

struct ReplicationPacket {	// server -> client
	std::uint16_t id;

	/*
	특정 타입
	해당 타입을 초기화하는데 필요한 모든 인자
	*/
	GROUP_TYPE groupType;
	Vec2 pos;
};

struct Packet {
	PacketType type;

	union /*PacketData*/ {
		LoginPacket lg;
		LoginResultPacket lr;
		RegisterPacket rg;
		MovePacket mv;
		InputPacket in;
		DestroyPacket ds;
		LeavePacket lv;
		LogoutPacket lo;
		ChangeScenePacket cs;
		ChangeSceneAckPacket ca;
		ReplicationPacket rp;
	};
};

#endif	// PROTOCOL_HPP