#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "struct.hpp"
#include <cstdint>

constexpr short PORT = 9000;
constexpr short BUFSIZE = 1024;

enum class PacketType {
	LOGIN,
	LEAVE,

	MOVE,

};

enum class Direction {
	E, W, S, N,
	NE, NW, SE, SW,
};

struct MovePacket {
	std::uint8_t id;
	Direction dir;
	Vec2 pos;
};

struct Packet {
	PacketType type;

	union /*PacketData*/ {
		MovePacket mv;
	};
};

#endif // PROTOCOL_HPP