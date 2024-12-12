#ifndef __PATH_HANDLER_HPP
#define __PATH_HANDLER_HPP

#include "define.hpp"
#include <filesystem>
namespace fs = std::filesystem;

class PathHandler {
	SINGLETON( PathHandler );

public:
	void init( );
	const fs::path & getContentPath( ) const { return contentPath_; }

private:
	fs::path contentPath_;
};

#endif // __PATH_HANDLER_HPP