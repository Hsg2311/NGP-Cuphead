#include "Animation.hpp"
#include "Texture.hpp"
#include "Timer.hpp"

void Animation::update( ) {
	accTime_ += fDT;

	if ( accTime_ >= animFrames_[ currFrame_ ].duration ) {
		accTime_ -= animFrames_[ currFrame_++ ].duration;
		currFrame_ %= animFrames_.size( );
	}
}

void Animation::render( HDC hdc, const Vec2& objPos ) {
	auto finalPos = objPos + animFrames_[ currFrame_ ].offset;

	tex_->Draw( hdc,
		static_cast<int>( finalPos.x - animFrames_[ currFrame_ ].sliceSize.x / 2.f ),
		static_cast<int>( finalPos.y - animFrames_[ currFrame_ ].sliceSize.y / 2.f ),
		static_cast<int>( animFrames_[ currFrame_ ].sliceSize.x ),
		static_cast<int>( animFrames_[ currFrame_ ].sliceSize.y ),
		static_cast<int>( animFrames_[ currFrame_ ].LT.x ),
		static_cast<int>( animFrames_[ currFrame_ ].LT.y ),
		static_cast<int>( animFrames_[ currFrame_ ].sliceSize.x ),
		static_cast<int>( animFrames_[ currFrame_ ].sliceSize.y ) );
}

void Animation::create( Texture* tex, Vec2 LT, Vec2 sliceSize,
						Vec2 step, float duration, UINT frameCount, Vec2 offset ) {
	tex_ = tex;

	animFrames_.reserve( frameCount );
	for ( auto i = 0u; i < frameCount; ++i ) {
		auto frame = frameInfo{
			.LT = LT + step * i,
			.sliceSize = sliceSize,
			.offset = offset,
			.duration = duration
		};

		animFrames_.emplace_back( frame );
	}
}
