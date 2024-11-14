#ifndef __ANIMATION_HPP
#define __ANIMATION_HPP

#include "struct.hpp"
#include <string>
#include <Windows.h>
#include <vector>

class Texture;

struct frameInfo {
	Vec2 LT;
	Vec2 sliceSize;
	float duration;
};

class Animation
{
public:
	Animation( ) 
		: animName_{ }, tex_{ nullptr }, animFrames_{ }
		, currFrame_{ 0 }, accTime_{ 0.f } {}
	~Animation( ) {}

	void setName( const std::wstring& animName ) { animName_ = animName; }
	const std::wstring& getName( ) const { return animName_; }

	void update( );
	void render( HDC hdc, const Vec2& objPos );
	void create( Texture* tex, Vec2 LT, Vec2 sliceSize,
				Vec2 step, float duration, UINT frameCount );

private:
	std::wstring animName_;
	Texture* tex_;
	std::vector<frameInfo> animFrames_;
	UINT currFrame_;
	float accTime_;
};

#endif // __ANIMATION_HPP