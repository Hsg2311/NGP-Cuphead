#ifndef OVERWORLD_FRIEND_HPP
#define OVERWORLD_FRIEND_HPP

#include "Object.hpp"
#include "Texture.hpp"
#include "Protocol.hpp"


class OverworldFriend : public Object {
public:
	OverworldFriend(const std::vector<texInfo>& info);
	virtual ~OverworldFriend() {}

	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void onCollision(Object* other) override;
	virtual void onCollisionEntry(Object* other) override;
	virtual void onCollisionExit(Object* other) override;



	virtual OverworldFriend* clone() override {
		return new OverworldFriend(*this);
	}
public:


private:
	std::vector<Texture*> textures_;
	Direction currentDirection = Direction::NONE;

};

#endif // OVERWORLD_PLAYER_HPP