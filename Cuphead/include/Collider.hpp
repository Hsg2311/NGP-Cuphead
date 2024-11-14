#ifndef __COLLIDER_HPP
#define __COLLIDER_HPP

#include "SelectGdiObject.hpp"
#include "struct.hpp"

class Collider {
public:
	Collider( ) 
		: offset_{ }
		, finalPos_{ }
		, scale_{ }
		, id_{ nextId_++ }
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

	UINT getID( ) const { return id_; }

public:
	void update( const Vec2& myObjPos ) { 
		// Object의 위치를 따라간다.
		finalPos_ = myObjPos + offset_;
		//assert( collisionCount_ >= 0 );
	}

	void render( HDC hdc ) {
		auto pen = PEN_TYPE::GREEN;

		if ( collisionCount_ )
			pen = PEN_TYPE::RED;

		SelectGdiObject gdiObject{ hdc, pen, BRUSH_TYPE::HOLLOW };

		Rectangle( hdc
			, static_cast<int>( finalPos_.x - scale_.x / 2.f )
			, static_cast<int>( finalPos_.y - scale_.y / 2.f )
			, static_cast<int>( finalPos_.x + scale_.x / 2.f )
			, static_cast<int>( finalPos_.y + scale_.y / 2.f ) );
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
	UINT id_;
	int collisionCount_;

	static UINT nextId_;
};

#endif // __COLLIDER_HPP