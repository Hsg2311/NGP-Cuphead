#include "Network.hpp"

<<<<<<< HEAD
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
=======

namespace network {

	void network::initNet( ) {
	}

	void network::closeNet( ) {
	}

	Exception::Exception( int line, const char* file, int error, std::string_view desc ) NET_NOEXCEPT
		: MyException( line, file ), error_( error ) {
	}
}

>>>>>>> 4a7d3951422e1aa00ff62c3f7f8d77d88525af52
