#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <iostream>
#include <atomic>

#define BUFSIZE 1024

extern std::atomic_bool flag;



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
		};

		struct Boss {
			int x, y;
			int hp;
			int entityId;
		};
		struct ClientStatePacket {
			short x, y;
			unsigned char hp;
		};

		struct EnemyStatePacket {
			short x, y;
			unsigned char entityId;
			unsigned char hp;
		};

		struct CollisionEventPacket {
			unsigned char entityId;
		};

		struct DeathEventPacket {
			unsigned char entityId;
		};

		struct LoadSaveFile {
			unsigned char stage;
		};
	};
};


enum class ClientPacketType : unsigned char {
	None,
	Input ,
	LogIn ,
	LogOut 
};


struct ClientPacket {
	ClientPacketType type;
	
	union {
		struct InputPacket {
			unsigned char entityId;
			unsigned char dir;
			unsigned char jump;
			unsigned char attack;
		}Input;
		struct SignUpOrLogInPacket {
			unsigned char username[50];
			unsigned char password[50];
		}LogIn;

		struct LogOutPacket {
			unsigned char username[50];
		}LogOut;
	};
};






#endif // PROTOCOL_HPP