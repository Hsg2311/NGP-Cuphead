#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <iostream>
#include <atomic>

#define BUFSIZE 1024

std::atomic_bool flag{ false };

enum class ServerPacketType : unsigned char {
	ClientStatePacket,
	EnemyStateUpdate,
	CollisionEvent,
	DeathEvent,
	//------------------------------------
	SignUp,
	LogIn,
	LogOut,

	CompletedSignUp,
	CompletedLogIn,
	CompletedLogOut,

	FailedSignUp,
	FailedLogIn,
	FailedLogOut,

	SaveLogfile
};

struct ServerPacket {
	ServerPacketType type;

	union {
		struct Player {
			int x, y;
			int hp;
			int entityId;
		}players;

		struct Boss {
			int x, y;
			int hp;
			int entityId;
		}boss;

		struct ClientStatePacket {
			short x, y;
			unsigned char hp;
		}clientState;

		struct EnemyStatePacket {
			short x, y;
			unsigned char entityId;
			unsigned char hp;
		}enemyState;

		struct CollisionEventPacket {
			unsigned char entityId;
		}collisionEvent;

		struct DeathEventPacket {
			unsigned char entityId;
		}deathEvent;

		struct LoadSaveFile {
			unsigned char stage;
		}loadSaveFile;
	};
};


enum class ClientPacketType : unsigned char {
	Input = 1,
	LogIn = 2,
	LogOut = 3
};


struct ClientPacket {
	ClientPacketType type;

	union {
		struct InputPacket {
			unsigned char entityId;
			unsigned char dir;
			unsigned char jump;
			unsigned char attack;
		};
		struct SignUpOrLogInPacket {
			std::string username;
			std::string password;
		};

		struct LogOutPacket {
			std::string username;
		};
	};
};






#endif // PROTOCOL_HPP