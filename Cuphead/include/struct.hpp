#ifndef __STRUCT_HPP
#define __STRUCT_HPP

#include <cassert>
#include <cmath>

struct Vec2 {
	float x;
	float y;

public:
	void Normalize( ) {
		auto hypotenuse = std::hypot( x, y );

		assert( hypotenuse != 0.f );

		x /= hypotenuse;
		y /= hypotenuse;
	}

public:
	Vec2( )
		: x{ 0.f }
		, y{ 0.f }
	{}
	
	Vec2( float x, float y )
		: x{ x }
		, y{ y }
	{}

	Vec2( int x, int y )
		: x{ static_cast<float>( x ) }
		, y{ static_cast<float>( y ) }
	{}

public:
	Vec2 operator+( const Vec2& rhs ) const	{
		return Vec2{ x + rhs.x, y + rhs.y };
	}

	Vec2 operator-( const Vec2& rhs ) const	{
		return Vec2{ x - rhs.x, y - rhs.y };
	}

	Vec2 operator*( float scalar ) const {
		return Vec2{ x * scalar, y * scalar };
	}

	Vec2 operator*( unsigned int scalar ) const {
		return Vec2{ x * (float)scalar, y * (float)scalar };
	}

	Vec2 operator/( float scalar ) const {
		assert( scalar != 0.f );

		return Vec2{ x / scalar, y / scalar };
	}

	Vec2& operator+=( const Vec2& rhs )	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vec2& operator-=( const Vec2& rhs )	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vec2& operator*=( float scalar ) {
		x *= scalar;
		y *= scalar;

		return *this;
	}

	Vec2& operator/=( float scalar ) {
		assert( scalar != 0.f );

		x /= scalar;
		y /= scalar;

		return *this;
	}
};

#endif // __STRUCT_HPP