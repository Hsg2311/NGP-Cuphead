#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32")

#include <string>
#include <string_view>
#include <cstdint>

#include <queue>

#include "MyException.hpp"

using namespace std::literals;

#define NET_NOEXCEPT noexcept
#define NET_EXCEPT(error, desc) network::Exception(__LINE__, __FILE__, error, desc)
#define NET_LAST_EXCEPT(desc) NET_EXCEPT(WSAGetLastError(), desc)

namespace network {

	void initNet( );
	void closeNet( );
	
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
			: sock_( createNativeSocket( ) ), open_( true ) {}

		

	private:
		static SOCKET createNativeSocket( ) {
			auto ret = socket( AF_INET, SOCK_STREAM, 0 );
			if ( ret == INVALID_SOCKET ) {
				throw NET_LAST_EXCEPT( "Failed to create TCP socket"sv );
			}
			return ret;
		}

		SOCKET sock_;
		bool open_;

	};
}



#endif // NETWORK_HPP