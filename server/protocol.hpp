#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "struct.hpp"
#include <cstdint>

constexpr short PORT = 9000;
constexpr short BUFSIZE = 1024;

enum class PacketType {
	NONE,

	LOGIN,
	LEAVE,

	MOVE,
	INPUT,
};

enum class Direction {
	NONE,

	E, W, S, N,
	NE, NW, SE, SW,
};

struct MovePacket {		// server -> client
	std::uint8_t id;
	Direction dir;
	Vec2 pos;
};

struct InputPacket {		// client -> server
	std::uint16_t id;
	bool left, right, up, down;
};

struct Packet {
	PacketType type;

	union /*PacketData*/ {
		MovePacket mv;
		InputPacket in;
	};

	
};

#endif	// PROTOCOL_HPP