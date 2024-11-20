#include "Background.hpp"
#include "ResourceHandler.hpp"
#include "Core.hpp"
#include "Camera.hpp"

Background::Background( const std::wstring& resKey, const std::wstring& fileName )
	: texture_{ ResourceHandler::getInst( ).loadTexture( resKey, std::wstring( L"/texture/background/" + fileName ) ) } {}

void Background::render( HDC hdc ) {
	auto renderPos = Camera::getInst( ).getRenderPos( getObjPos( ) );
	auto xDest = static_cast<int>( renderPos.x - Core::getInst( ).getResolution( ).x / 2.f );
	auto yDest = static_cast<int>( renderPos.y - Core::getInst( ).getResolution( ).y / 2.f );

	auto destWidth = Core::getInst( ).getResolution( ).x;
	auto destHeight = Core::getInst( ).getResolution( ).y;
	auto srcWidth = texture_->getWidth( );
	auto srcHeight = texture_->getHeight( );

	texture_->draw( hdc, xDest, yDest, srcWidth, srcHeight,
					0, 0, srcWidth, srcHeight );

	componentRender( hdc );
}

BackgroundAnim::BackgroundAnim( const std::wstring& resKey, const std::wstring& fileName,
								float duration, UINT frameCount ) {
	auto texture = ResourceHandler::getInst( ).loadTexture( resKey, std::wstring( L"/texture/background/" + fileName ) );

	// 애니메이션할 이미지의 한 프레임의 너비와 높이
	auto width = static_cast<float>( texture->getWidth( ) / frameCount );
	auto height = static_cast<float>( texture->getHeight( ) );

	createAnimator( );
	getAnimator( )->createAnimation( resKey, texture, Vec2( 0.f, 0.f ),
									Vec2( width, height ), Vec2( width, 0.f ),
									duration, frameCount );
	getAnimator( )->play( resKey );
}

void BackgroundAnim::render( HDC hdc ) {
	componentRender( hdc );
}
