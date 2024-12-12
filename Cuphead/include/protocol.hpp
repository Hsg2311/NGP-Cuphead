#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "struct.hpp"
#include "define.hpp"

#include <cstdint>

constexpr short PORT = 9000;
constexpr short BUFSIZE = 1024;
static std::uint16_t sId = 0;

enum class PacketType {
	NONE,

	LOGIN,
	LOGIN_RESULT,
	LEAVE,

	REGISTER,
	DESTROY,
	MOVE,
	INPUT,
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
};

struct RegisterPacket {	// server -> client
	std::uint16_t id;

	/*
	Ư�� Ÿ��
	�ش� Ÿ���� �ʱ�ȭ�ϴµ� �ʿ��� ��� ����
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

struct Packet {
	PacketType type;

	union /*PacketData*/ {
		LoginPacket lg;
		LoginResultPacket lr;
		RegisterPacket rg;
		MovePacket mv;
		InputPacket in;
		DestroyPacket ds;
	};
};

#endif	// PROTOCOL_HPP