#include "IDHandler.hpp"

std::optional<std::uint16_t> IDHandler::allocID( ) {
	if ( idList_.empty( ) ) {
		return std::nullopt;
	}

	std::uint16_t id = idList_.front( );
	idList_.pop_front( );

	return id;
}

IDHandler::IDHandler( )
	: idList_( std::numeric_limits<std::uint16_t>::max( ) ) {}

IDHandler::~IDHandler( ) = default;