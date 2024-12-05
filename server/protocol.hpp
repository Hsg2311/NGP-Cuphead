#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "struct.hpp"
#include <cstdint>

constexpr short PORT = 9000;
constexpr short BUFSIZE = 1024;

enum class PacketType {
	NONE,

	LOGIN,
	LOGIN_RESULT,
	LEAVE,

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

struct MovePacket {		// server -> client
	std::uint8_t id;
	Direction dir;
	Vec2 pos;
};

struct InputPacket {	// client -> server
	std::uint16_t id;
	bool left, right, up, down;
};

struct Packet {
	PacketType type;

	union /*PacketData*/ {
		LoginPacket lg;
		LoginResultPacket lr;
		MovePacket mv;
		InputPacket in;
	};
};

#endif	// PROTOCOL_HPP