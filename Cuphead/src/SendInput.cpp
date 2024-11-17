#include "Player.hpp"
#include "protocol.hpp"

char buf[sizeof(InputPacket)];

void Player::sendInput(InputPacket packet)
{
	memset(buf, 0, sizeof(buf));
	memcpy(buf, &packet, sizeof(InputPacket));

	/*int retval = send(sock_, buf, sizeof(buf), 0)*/
}