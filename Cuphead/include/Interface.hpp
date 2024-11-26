#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "framework.h"
#include "Protocol.hpp"
#include <thread>


class Interface
{
public:
	ClientPacket packetInput;
	void checkData();

};

#endif // INTERFACE_HPP