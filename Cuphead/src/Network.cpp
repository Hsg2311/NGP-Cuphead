#include "Network.hpp"

namespace network {

	Exception::Exception( int line, const char* file, int error, std::string_view desc ) NET_NOEXCEPT
		: MyException( line, file ), error_( error ) {
		whatBuffer_ += "[Error: " + std::to_string( error ) + "] "
			+ desc.data( ) + "\n\n";

		whatBuffer_ += std::system_category( ).message( error_ );
	}

	std::string getCounterpartIp( TcpSocket& sock ) {
		auto ip = std::array<char, INET_ADDRSTRLEN>( );
		inet_ntop( AF_INET, &sock.getAddr( ), ip.data( ), ip.size( ) );
		return ip.data( );
	}

}	// namespace network