#ifndef OVERWORLD_PLAYER_HPP
#define OVERWORLD_PLAYER_HPP

#include "Object.hpp"

class OverworldPlayer : public Object {
public:
	OverworldPlayer( );
	virtual ~OverworldPlayer( ) {}

	virtual void update( ) override;

	virtual void onCollision( Object* other ) override;
	virtual void onCollisionEntry( Object* other ) override;
	virtual void onCollisionExit( Object* other ) override;

	virtual OverworldPlayer* clone( ) override { 
		return new OverworldPlayer( *this );
	}
};

#endif // OVERWORLD_PLAYER_HPP