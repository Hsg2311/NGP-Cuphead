#ifndef __COLLIDER_HPP
#define __COLLIDER_HPP

#include "struct.hpp"

class Collider {
public:
	Collider( ) 
		: offset_{ }
		, finalPos_{ }
		, scale_{ }
		, collisionCount_{ 0 }
	{}

	Collider( const Collider& ) = delete;
	Collider( Collider&& ) = delete;

	Collider& operator=( const Collider& ) = delete;
	Collider& operator=( Collider&& ) = delete;

public:
	void setOffset( const Vec2& offset ) { offset_ = offset; }
	void setScale( const Vec2& scale ) { scale_ = scale; }

	Vec2 getOffset( ) const { return offset_; }
	Vec2 getScale( ) const { return scale_; }
	Vec2 getFinalPos( ) const { return finalPos_; }

public:
	void update( const Vec2& myObjPos ) { 
		// Object의 위치를 따라간다.
		finalPos_ = myObjPos + offset_;
		//assert( collisionCount_ >= 0 );
	}

public:
	// 충돌 진입 시 처리
	void addCollisionCount( ) { ++collisionCount_; }

	// 충돌 종료 시 처리
	void subCollisionCount( ) {
		--collisionCount_;
		assert( collisionCount_ >= 0 );
	}

private:
	Vec2 offset_;
	Vec2 finalPos_;
	Vec2 scale_;
	int collisionCount_;
};

#endif // __COLLIDER_HPP