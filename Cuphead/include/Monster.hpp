#ifndef __MONSTER_HPP
#define __MONSTER_HPP

#include "Object.hpp"
#include "struct.hpp"
#include <Windows.h>

class Monster : public Object {
public:
	Monster( );
	virtual ~Monster( );

public:
	void setSpeed( float speed ) { speed_ = speed; }
	void setMaxDistance( float maxDistance ) { maxDistance_ = maxDistance; }

	float getSpeed( ) const { return speed_; }

	void setCenterPos( const Vec2& centerPos ) { centerPos_ = centerPos; }

public:
	virtual void update( ) override;
	virtual void render( HDC hdc ) override;

public:
	virtual void OnCollision( Object* other ) override;
	virtual void OnCollisionEntry( Object* other ) override;
	virtual void OnCollisionExit( Object* other ) override;

public:
	virtual Monster* clone( ) override { return new Monster{ *this }; }

private:
	Vec2 centerPos_;
	float speed_;
	float maxDistance_;
	int dir_;
	int hp_;
};

#endif // __MONSTER_HPP