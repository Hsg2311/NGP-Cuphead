#ifndef __ANIMATOR_HPP
#define __ANIMATOR_HPP

#include "func.hpp"
#include "Animation.hpp"
#include "struct.hpp"
#include <map>
#include <string>

class Texture;

class Animator {
public:
	Animator( ) : animations_{ }, currAnim_{ nullptr } {}
	~Animator( ) { Safe_Delete_Map( animations_ ); }

	void createAnimation( const std::wstring& animName, Texture* tex, Vec2 LT, 
		Vec2 sliceSize, Vec2 step, float duration, UINT frameCount, Vec2 offset = { 0.f, 0.f } );
	Animation* findAnimation( const std::wstring& animName );
	void play( const std::wstring& animName );

	void update( ) {
		if( currAnim_ )
			currAnim_->update( );
	}

	void render( HDC hdc, const Vec2& objPos ) {
		if ( currAnim_ )
			currAnim_->render( hdc, objPos );
	}

private:
	std::map<std::wstring, Animation*> animations_;
	Animation* currAnim_;
};

#endif // __ANIMATOR_HPP