#ifndef OVERWORLD_PLAYER_HPP
#define OVERWORLD_PLAYER_HPP

#include "Object.hpp"
#include "Texture.hpp"
#include "Protocol.hpp"
//enum class Direction {
//	UP,
//	DOWN,
//	LEFT,
//	RIGHT,
//	LEFT_UP,
//	RIGHT_UP,
//	LEFT_DOWN,
//	RIGHT_DOWN,
//};

class OverworldPlayer : public Object {
public:
	OverworldPlayer( const std::vector<texInfo>& info );
	virtual ~OverworldPlayer( ) {}

	virtual void update( ) override;
	virtual void render( HDC hdc ) override;

	virtual void onCollision( Object* other ) override;
	virtual void onCollisionEntry( Object* other ) override;
	virtual void onCollisionExit( Object* other ) override;
	virtual uint16_t getId() override;
	

	virtual OverworldPlayer* clone( ) override { 
		return new OverworldPlayer( *this );
	}
public:
	void moveInputPacket();

private:
	std::vector<Texture*> textures_;
	Direction currentDirection = Direction::NONE;

};

#endif // OVERWORLD_PLAYER_HPP