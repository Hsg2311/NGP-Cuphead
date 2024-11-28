#ifndef SERVERCL_HPP
#define SERVERCL_HPP

#include "framework.h"
#include "PacketQueue.hpp"
#include "SendingStorage.hpp"
#include "Protocol.hpp"

#include <atomic>
#include <thread>
class ServerCL
{
public:
	ServerCL();
	~ServerCL();

	static void clientRecv(SOCKET sock);

	static void clientSend(SOCKET sock);



	
};

#endif // SERVERCL_HPP