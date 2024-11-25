#ifndef SERVERCL_HPP
#define SERVERCL_HPP

#include <Core.hpp>
#include <thread>
class ServerCL
{
public:
	ServerCL();
	~ServerCL();

	static void clientRecv();

	static void clientSend();

	void clientProcessPacket();

	void processLogSystem();
};

#endif // SERVERCL_HPP