#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

#include "Network.hpp"
#include "Protocol.hpp"


//Player players[2];


void processPacket(ClientPacketType type, char* buf, int bufSize)
{
	switch (type) {
	case ClientPacketType::Input:
	{
		ClientPacket::InputPacket* p = reinterpret_cast<ClientPacket::InputPacket*>(buf);

		break;
	}

	case ClientPacketType::LogIn: {
		ClientPacket::SignUpOrLogInPacket* p = reinterpret_cast<ClientPacket::SignUpOrLogInPacket*>(buf);

		std::ifstream in{ "userInfo.txt" };
		if (!in) {
			std::cerr << "파일을 열 수 없습니다. 새로 생성합니다." << std::endl;
			// 파일이 없는 경우 새로 생성 준비
			std::ofstream out{ "userInfo.txt", std::ios::app };
			if (!out) {
				std::cerr << "파일 생성 실패!" << std::endl;
				exit(1);
			}
			out.close();
			in.open("userInfo.txt");
		}

		// 사용자 정보 검색
		bool userExists = false;
		std::string line;
		while (std::getline(in, line)) {
			if (line.empty()) continue; // 빈 줄 건너뜀

			size_t delimiterPos = line.find(':');
			if (delimiterPos == std::string::npos) {
				std::cerr << "파일 형식이 잘못되었습니다." << std::endl;
				continue;
			}


			std::string fileUsername = line.substr(0, delimiterPos);
			std::string filePassword = line.substr(delimiterPos + 1);

			if (fileUsername == p->username) { // ID가 이미 존재하는 경우
				userExists = true;
				if (filePassword == p->password) {
					std::cout << "로그인 성공!" << std::endl;
					p->username = fileUsername;
					p->password = filePassword;
				}
				else {
					std::cerr << "비밀번호가 틀렸습니다." << std::endl;
				}
				break;
			}
		}
		in.close();

		if (!userExists) {
			// 새로운 유저 등록
			std::ofstream out{ "userInfo.txt", std::ios::app };
			if (!out) {
				std::cerr << "파일 열기 실패!" << std::endl;
				exit(1);
			}
			out << p->username << ":" << p->password << "\n";
			out.close();
			break;
		}
	}
	case ClientPacketType::LogOut: {

		break;
	}


	}
}

DWORD WINAPI recvThread(LPARAM sock_)
{
	SOCKET sock = static_cast<SOCKET>(sock_);
	//패킷타입, 패킷 사이즈, 데이터

	ClientPacketType type;
	int retval = recv(sock_, (char*)&type, sizeof(type), 0);
	if (retval == SOCKET_ERROR) {
		std::cerr << "type_recv_error " << WSAGetLastError() << std::endl;
	}

	short packSize;
	int retval = recv(sock_, (char*)packSize, sizeof(packSize), 0);
	if (retval == SOCKET_ERROR) {
		std::cerr << "packet_recv_error " << WSAGetLastError() << std::endl;
	}

	char buf[sizeof(packSize)];

	int retval = recv(sock_, (char*)buf, packSize, 0);
	if (retval == SOCKET_ERROR) {
		std::cerr << "packet_recv_error " << WSAGetLastError() << std::endl;
	}

	processPacket(type, buf, packSize);
}