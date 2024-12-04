#include "UserInterface.hpp"
#include "ResourceHandler.hpp"

#include <ranges>
#include <algorithm>

UserInterface::UserInterface( const std::vector<texInfo>& info ) {
	std::ranges::for_each( info, [this]( const texInfo& elem ) {
		textures_.push_back( 
			ResourceHandler::getInst( ).loadTexture( elem.resKey, std::wstring( L"/texture/ui/" + elem.fileName ) )
		);
	} );

	currTex_ = textures_.front( );
}

void UserInterface::render( HDC hdc ) {
	auto imageWidth = currTex_->getWidth( );
	auto imageHeight = currTex_->getHeight( );

	auto xDest = static_cast<int>( getObjPos( ).x - imageWidth / 2.f );
	auto yDest = static_cast<int>( getObjPos( ).y - imageHeight / 2.f );

	currTex_->draw( hdc, xDest, yDest, imageWidth, imageHeight,
		0, 0, imageWidth, imageHeight );
}
