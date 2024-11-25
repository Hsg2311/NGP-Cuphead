#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include "Object.hpp"
#include <Windows.h>

class Texture;

class Player : public Object {
public:
	Player( );
	virtual ~Player( );

	virtual void update( ) override;
	virtual void render( HDC hdc ) override;

	void createProjectile( );

	virtual void onCollision( Object* other ) override;
	virtual void onCollisionEntry( Object* other ) override;
	virtual void onCollisionExit( Object* other ) override;

	virtual Player* clone( ) override { return new Player{ *this }; }
};

#endif // __PLAYER_HPP