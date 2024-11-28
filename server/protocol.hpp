#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

constexpr short PORT = 9000;
constexpr short BUFSIZE = 1024;

enum class PacketType {
	MOVE,
	LEAVE,
};

struct Packet {
	PacketType type;

	union PacketData {

	};
};

#endif // PROTOCOL_HPP