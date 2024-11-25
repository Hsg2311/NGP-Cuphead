#include "Network.hpp"


namespace network {

	void network::initNet( ) {
	}

	void network::closeNet( ) {
	}

	Exception::Exception( int line, const char* file, int error, std::string_view desc ) NET_NOEXCEPT
		: MyException( line, file ), error_( error ) {
	}
}