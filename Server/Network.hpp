#ifndef NETWORK_HPP
#define NETWORK_HPP

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32")

#include <string>
#include <string_view>
#include <cstdint>
#include <array>

#include "MyException.hpp"
#include <system_error>

using namespace std::literals;

#define NET_NOEXCEPT noexcept
#define NET_EXCEPT(error, desc) network::Exception(__LINE__, __FILE__, error, desc)
#define NET_LAST_EXCEPT(desc) NET_EXCEPT(WSAGetLastError(), desc)

namespace network {
	
	class Exception : public MyException {
	public:
		Exception( int line, const char* file, int error, std::string_view desc ) NET_NOEXCEPT;

		const char* type( ) const NET_NOEXCEPT override {
			return "Network Exception";
		}
		int error( ) const NET_NOEXCEPT {
			return error_;
		}

	private:
		int error_;
	};

	class Ipv4Addr {
	public:
		Ipv4Addr( std::string_view ip = "127.0.0.1"sv )
			: present_( ip ), addr_( ) {
			if ( inet_pton( AF_INET, present_.data( ), &addr_ ) != 1 ) {
				throw NET_LAST_EXCEPT( "Failed to convert IPv4 address"sv );
			}
		}

		Ipv4Addr( std::uint32_t addr )
			: present_( 15u, '\0' ), addr_( addr ) {
			if ( inet_ntop( AF_INET, &addr_, present_.data( ), present_.size( ) ) == nullptr ) {
				throw NET_LAST_EXCEPT( "Failed to convert IPv4 address"sv );
			}
		}

		Ipv4Addr( const sockaddr& addr ) NET_NOEXCEPT
			: present_( ), addr_( reinterpret_cast<const sockaddr_in*>( &addr )->sin_addr.s_addr ) {}
		
		Ipv4Addr( const sockaddr_in& addr ) NET_NOEXCEPT
			: present_( ), addr_( addr.sin_addr.s_addr ) {}

		std::string_view present( ) const NET_NOEXCEPT {
			return present_;
		}
		std::uint32_t get( ) const NET_NOEXCEPT {
			return addr_;
		}

	private:
		std::string present_;
		std::uint32_t addr_;
	};

	class Port {
	public:
		Port( std::uint16_t hostPort = 0 ) NET_NOEXCEPT : port_( htons( hostPort ) ) {}	

		std::uint16_t get( ) const NET_NOEXCEPT {
			return port_;
		}

	private:
		std::uint16_t port_;
	};

	class SockAddr {
	private:
		union UAddr {
			sockaddr addr;
			sockaddr_in addr_in;

			UAddr( ) NET_NOEXCEPT = default;

			UAddr( const Ipv4Addr& ip, Port port ) NET_NOEXCEPT
				: addr_in{
					.sin_family = static_cast<decltype( sockaddr_in::sin_family )>( AF_INET ),
					.sin_port = static_cast<decltype( sockaddr_in::sin_port )>( port.get( ) )
				} {
				addr_in.sin_addr.s_addr = ip.get( );
			}

			UAddr( const sockaddr& addr ) NET_NOEXCEPT
				: addr( addr ) {}
		} uAddr_;

	public:
		SockAddr( ) NET_NOEXCEPT = default;

		SockAddr( const Ipv4Addr& ip, Port port ) NET_NOEXCEPT
			: uAddr_( ip, port ) {}

		SockAddr( const sockaddr& addr ) NET_NOEXCEPT
			: uAddr_( addr ) {}

		UAddr& get( ) NET_NOEXCEPT {
			return uAddr_;
		}

		const UAddr& get( ) const NET_NOEXCEPT {
			return uAddr_;
		}

		std::size_t size( ) const NET_NOEXCEPT {
			return sizeof( uAddr_.addr );
		}
	};
	
	class TcpSocket {
	public:
		TcpSocket( )
			: sock_( createNativeSocket( ) ), addr_( ), open_( true ) {}

		TcpSocket( SOCKET sock, bool bOpen = true ) NET_NOEXCEPT
			: sock_( sock ), addr_( ), open_( bOpen ) {}

		TcpSocket( SOCKET sock, const SockAddr& addr, bool bOpen = true ) NET_NOEXCEPT
			: sock_( sock ), addr_( addr ), open_( bOpen ) {}

		~TcpSocket( ) {
			if ( open_ ) {
				closesocket( sock_ );
			}
		}

		TcpSocket( const TcpSocket& other ) = delete;
		TcpSocket& operator=( const TcpSocket& other ) = delete;

		TcpSocket( TcpSocket&& other ) noexcept
			: sock_( std::exchange( other.sock_, INVALID_SOCKET ) )
			, addr_( std::exchange( other.addr_, SockAddr( ) ) )
			, open_( std::exchange( other.open_, false ) ) {}

		TcpSocket& operator=( TcpSocket&& other ) noexcept {
			if ( open_ ) {
				closesocket( sock_ );
			}

			sock_ = std::exchange( other.sock_, INVALID_SOCKET );
			addr_ = std::exchange( other.addr_, SockAddr( ) );
			open_ = std::exchange( other.open_, false );

			return *this;
		}

		void bind( const SockAddr& addr ) {
			addr_ = addr;
			if ( ::bind( sock_, &addr_.get( ).addr, static_cast<int>( addr.size( ) ) ) == SOCKET_ERROR ) {
				throw NET_LAST_EXCEPT( "Failed to bind TCP socket"sv );
			}
		}

		void listen( std::size_t backlog = SOMAXCONN ) {
			if ( ::listen( sock_, static_cast<int>( backlog ) ) == SOCKET_ERROR ) {
				throw NET_LAST_EXCEPT( "Failed to listen TCP socket"sv );
			}
		}

		void connect( const SockAddr& addr ) {
			addr_ = addr;
			if ( ::connect( sock_, &addr_.get( ).addr, static_cast<int>( addr.size( ) ) ) == SOCKET_ERROR ) {
				throw NET_LAST_EXCEPT( "Failed to connect TCP server"sv );
			}
		}

		std::size_t send( const void* data, std::size_t size ) {
			int sendSize = ::send( sock_, static_cast<const char*>( data ), static_cast<int>( size ), 0 );
			if ( sendSize < 0 ) {
				throw NET_LAST_EXCEPT( "Failed to send data"sv );
			}
			return sendSize;
		}

		std::size_t recv( char* data, std::size_t size ) {
			int recvSize = ::recv( sock_, data, static_cast<int>( size ), MSG_WAITALL );
			if ( recvSize < 0 ) {
				throw NET_LAST_EXCEPT( "Failed to receive data"sv );
				return 0;
			}
			return recvSize;
		}

		int sendUc( const void* data, std::size_t size ) {
			return ::send( sock_, static_cast<const char*>( data ), static_cast<int>( size ), 0 );
		}

		int recvUc( char* data, std::size_t size ) {
			return ::recv( sock_, data, static_cast<int>( size ), MSG_WAITALL );
		}

		TcpSocket accept( ) {
			auto tmp = SockAddr( );
			return accept( tmp );
		}

		TcpSocket accept( SockAddr& addr ) {
			int addrSize = static_cast<int>( addr.size( ) );
			SOCKET client = ::accept( sock_, &addr.get( ).addr, &addrSize );
			if ( client == INVALID_SOCKET ) {
				throw NET_LAST_EXCEPT( "Failed to accept TCP connection"sv );
			}
			return TcpSocket( client, addr );
		}

		TcpSocket acceptUc( ) {
			auto tmp = SockAddr( );
			return acceptUc( tmp );
		}

		TcpSocket acceptUc( SockAddr& addr ) {
			int addrSize = static_cast<int>( addr.size( ) );
			SOCKET client = ::accept( sock_, &addr.get( ).addr, &addrSize );
			if ( client == INVALID_SOCKET ) {
				return TcpSocket( INVALID_SOCKET, false );
			}
			return TcpSocket( client, addr );
		}

		void close( ) {
			if ( closesocket( sock_ ) == SOCKET_ERROR ) {
				throw NET_LAST_EXCEPT( "Failed to close TCP socket"sv );
			}
			open_ = false;
		}

		void open( ) {
			if ( open_ ) {
				throw NET_EXCEPT( WSAEISCONN, "Socket is already open"sv );
			}

			sock_ = createNativeSocket( );
			open_ = true;
		}

		bool invalid( ) const NET_NOEXCEPT {
			return sock_ == INVALID_SOCKET;
		}

		IN_ADDR& getAddr( ) NET_NOEXCEPT {
			return addr_.get( ).addr_in.sin_addr;
		}

		USHORT getPort( ) NET_NOEXCEPT {
			return addr_.get( ).addr_in.sin_port;
		}

		SOCKET& getSock( ) NET_NOEXCEPT {
			return sock_;
		}

	private:
		static SOCKET createNativeSocket( ) {
			auto ret = socket( AF_INET, SOCK_STREAM, 0 );
			if ( ret == INVALID_SOCKET ) {
				throw NET_LAST_EXCEPT( "Failed to create TCP socket"sv );
			}
			return ret;
		}

		SOCKET sock_;
		SockAddr addr_;
		bool open_;
	};

	std::string getCounterpartIp( TcpSocket& sock );

}	// namespace network

#endif // NETWORK_HPP

//enum class 
// : std::uint16_t {
//	move,
//	chat,
//	join,
//	leave,
//};
//
//struct MovePacket { /* ... */ };
//struct ChatPacket { /* ... */ };
//struct JoinPacket { /* ... */ };
//struct LeavePacket { /* ... */ };
//
//struct Packet {
//	PacketType type;
//	std::uint16_t size;
//
//	union /* PacketData*/ {
//		MovePacket mv;
//		ChatPacket ct;
//		JoinPacket jo;
//		LeavePacket le;
//	};
//};
//
//void foo( ) {
//	Packet p;
//	p.type = PacketType::move;
//	p.size = sizeof( MovePacket );
//	p.mv = MovePacket{ /* ... */ };
//}
//
//union pacekt {
//	// pakcet type = move
//	// struct move packet
//	// struct 
//	// struct
//	// struct
//	// struct
//	// struct
//};