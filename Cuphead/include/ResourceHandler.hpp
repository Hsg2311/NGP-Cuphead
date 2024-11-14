#ifndef __RESOURCE_HANDLER_HPP
#define __RESOURCE_HANDLER_HPP

#include "define.hpp"
#include <map>
#include <string>

class Res;
class Texture;

class ResourceHandler {
	SINGLETON( ResourceHandler );

public:
	Texture* LoadTexture( const std::wstring& resKey, const std::wstring& relativePath );
	Texture* FindTexture( const std::wstring& resKey );

private:
	std::map<std::wstring, Res*> texMap_;
};

#endif // __RESOURCE_HANDLER_HPP