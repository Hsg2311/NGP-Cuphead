#ifndef SERVERCL_HPP
#define SERVERCL_HPP

#include "framework.h"

#include <thread>
class ServerCL
{
public:
	ServerCL();
	~ServerCL();

	static void clientRecv(SOCKET sock);

	static void clientSend(SOCKET sock);

	void clientProcessPacket();

	void processLogSystem();
};

#endif // SERVERCL_HPP