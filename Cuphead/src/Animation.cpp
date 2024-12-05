#include "Animation.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include "Camera.hpp"

void Animation::update( ) {
	accTime_ += fDT;

	if ( accTime_ >= animFrames_[ currFrame_ ].duration ) {
		accTime_ -= animFrames_[ currFrame_ ].duration;
		++currFrame_;

		currFrame_ %= animFrames_.size( );
	}
}

void Animation::render( HDC hdc, const Vec2& objPos ) {
<<<<<<< HEAD
	auto finalPos = objPos + animFrames_[ currFrame_ ].offset;
	finalPos = Camera::getInst( ).getRenderPos( finalPos );	// 카메라 위치에 따라 렌더링 위치 조정

	tex_->draw( hdc,
		static_cast<int>( finalPos.x - animFrames_[ currFrame_ ].sliceSize.x / 2.f ),
		static_cast<int>( finalPos.y - animFrames_[ currFrame_ ].sliceSize.y / 2.f ),
=======
	tex_->Draw( hdc,
		static_cast<int>( objPos.x - animFrames_[ currFrame_ ].sliceSize.x / 2.f ),
		static_cast<int>( objPos.y - animFrames_[ currFrame_ ].sliceSize.y / 2.f ),
>>>>>>> 4a7d3951422e1aa00ff62c3f7f8d77d88525af52
		static_cast<int>( animFrames_[ currFrame_ ].sliceSize.x ),
		static_cast<int>( animFrames_[ currFrame_ ].sliceSize.y ),
		static_cast<int>( animFrames_[ currFrame_ ].LT.x ),
		static_cast<int>( animFrames_[ currFrame_ ].LT.y ),
		static_cast<int>( animFrames_[ currFrame_ ].sliceSize.x ),
		static_cast<int>( animFrames_[ currFrame_ ].sliceSize.y ) );
}

void Animation::create( Texture* tex, Vec2 LT, Vec2 sliceSize,
						Vec2 step, float duration, UINT frameCount ) {
	tex_ = tex;

	animFrames_.reserve( frameCount );
	for ( auto i = 0u; i < frameCount; ++i ) {
		auto frame = frameInfo{
			.LT = LT + step * i,
			.sliceSize = sliceSize,
			.duration = duration
		};

		animFrames_.emplace_back( frame );
	}
}
