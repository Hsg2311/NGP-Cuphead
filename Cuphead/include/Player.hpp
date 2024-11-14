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

	void CreateProjectile( );

	virtual void OnCollision( Object* other ) override;
	virtual void OnCollisionEntry( Object* other ) override;
	virtual void OnCollisionExit( Object* other ) override;

	virtual Player* clone( ) override { return new Player{ *this }; }
};

#endif // __PLAYER_HPP