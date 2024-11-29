#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "struct.hpp"
#include "define.hpp"
#include <cstdint>

constexpr short PORT = 9000;
constexpr short BUFSIZE = 1024;

enum class PacketType {
	NONE,
	REGIST,
	LOGIN,
	LEAVE,

	MOVE,

};

enum class Direction {
	NONE,

	E, W, S, N,
	NE, NW, SE, SW,
};

struct MovePacket {
	std::uint8_t id;
	Direction dir;
	Vec2 pos;
};

struct RegistPacket {
	std::uint16_t id;
	GROUP_TYPE groupType;
};

struct Packet {
	PacketType type;

	union /*PacketData*/ {
		MovePacket mv;
		RegistPacket rs;
	};

	Packet()
	: type(PacketType::NONE), mv(){
	}
};

#endif // PROTOCOL_HPP