#ifndef __CORE_HPP
#define __CORE_HPP

#include "Network.hpp"
#include "define.hpp"
#include "protocol.hpp"

#include <array>
#include "WinUT.hpp"
#include <mutex>
#include <queue>
#include <unordered_map>

class Object;

class PacketQueue {
public:

	static PacketQueue& getInst() {
		static PacketQueue instance;
		return instance;
	} 

	void pushPacket( const Packet& packet );
	void dispatch( );
	void addObject( Object* obj );
	Object* getObject( std::uint16_t id ) {
		return networkIdToObject[ id ];
	}

private:
	std::queue<Packet> packetQueue_;
	std::mutex queueMtx_;

	std::unordered_map<int, Object*> networkIdToObject;
	std::unordered_map<Object*, int> objectToNetworkId;
};

class Core {
	SINGLETON( Core );

public:
	int init( HWND hWnd, POINT resolution );
	void progress( );
	void createPenBrush( );

	HWND getHwnd( ) const { return hWnd_; }
	POINT getResolution( ) const { return resolution_; }
	HPEN getPen( PEN_TYPE type ) const { return hPen_[ static_cast<UINT>( type ) ]; }
	HBRUSH getBrush( BRUSH_TYPE type ) const { return hBrush_[ static_cast<UINT>( type ) ]; }

	void sendLoginPacket( const char id[ 16 ], const char pw[ 16 ] );

private:
	HWND hWnd_;
	POINT resolution_;
	HDC hdc_;

	HBITMAP hBitmap_;
	HDC hMemDC_;

	std::thread sendThread_;
	std::thread recvThread_;
	network::TcpSocket serverSock_;

	std::array<HPEN, static_cast<UINT>( PEN_TYPE::EOE )> hPen_;
	std::array<HBRUSH, static_cast<UINT>( BRUSH_TYPE::EOE )> hBrush_;
};

#endif // __CORE_HPP