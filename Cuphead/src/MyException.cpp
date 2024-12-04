#include "MyException.hpp"

#include <sstream>

MyException::MyException( int lineNum, const char* fileStr ) noexcept
    : lineNum_( lineNum ), fileStr_( fileStr )
{}

const char* MyException::what( ) const noexcept {
    auto oss = std::ostringstream( );
    
    oss << type( ) << '\n'
        << metaStr( ) << '\n';
    whatBuffer_.insert( 0, oss.str( ) );
	return whatBuffer_.c_str( );
}

std::string MyException::metaStr( ) const noexcept {
    auto oss = std::ostringstream( );

	oss << "[File] " << fileStr( ) << '\n'
		<< "[Line] " << lineNum( ) << '\n';
    return oss.str( );
}
