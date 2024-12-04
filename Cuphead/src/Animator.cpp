#include "Animator.hpp"
#include <cassert>

void Animator::createAnimation( const std::wstring& animName, Texture* tex, Vec2 LT,
								Vec2 sliceSize, Vec2 step, float duration, UINT frameCount, Vec2 offset ) {
	auto anim = findAnimation( animName );
	assert( anim == nullptr );
	
	anim = new Animation{ };
	anim->setName( animName );
	anim->create( tex, LT, sliceSize, step, duration, frameCount, offset );
	
	animations_.insert( { animName, anim } );
}

Animation* Animator::findAnimation( const std::wstring& animName ) {
	auto anim = animations_.find( animName );

	if ( anim == animations_.end( ) )
		return nullptr;

	assert( anim->second != nullptr );

	return anim->second;
}

void Animator::play( const std::wstring& animName ) {
	currAnim_ = findAnimation( animName );
	assert( currAnim_ != nullptr );
}
