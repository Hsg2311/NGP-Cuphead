#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "framework.h"
#include "Protocol.hpp"
#include "define.hpp"
#include <thread>


class Interface
{
	SINGLETON(Interface);
public:
	

	ClientPacket packet;
	void checkData() {
		if (packet.type != ClientPacketType::None) { flag = TRUE; }
	}

	void setPacketInput(const ClientPacket& newPacket) { packet = newPacket; }

	const ClientPacket& getPacketInput() const { return packet; }

};

#endif // INTERFACE_HPP