#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "framework.h"
#include "Protocol.hpp"
#include <thread>


class Interface
{
public:
	InputPacket packetInput{};
	void checkData();
	InputPacket getData() { return packetInput; }
	void intiallizeData(){ packetInput = { ClientPacketType::Input, 0, 0, 0, 0 }; }
	
};

#endif // INTERFACE_HPP