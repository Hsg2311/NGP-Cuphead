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

	void setId(std::uint16_t id) { networkId_ = id; }
	void setPosition(const Vec2& pos) { objPos_ = pos; }

	std::uint16_t getNetworkId() { return networkId_; }
	Vec2 getPosition() const { return objPos_; }

private:
	Vec2 objPos_;
	std::uint16_t networkId_;
};

