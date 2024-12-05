#pragma once
#include "struct.hpp"

class Object
{
public:
	Object() 
		:objPos_{}
		, networkId_{}
	{}
	~Object();
	Object(const Object& other)
		:objPos_ {other.objPos_}
	{}


private:
	Vec2 objPos_;
	std::uint16_t networkId_;
};

