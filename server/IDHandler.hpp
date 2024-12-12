#ifndef ID_HANDLER_HPP
#define ID_HANDLER_HPP

#include "define.hpp"

#include <forward_list>
#include <cstdint>
#include <limits>
#include <optional>

class IDHandler {
	SINGLETON( IDHandler );

public:
	std::optional<std::uint16_t> allocID( );

	void deallocID( std::uint16_t id ) {
		idList_.push_front( id );
	}

private:
	std::forward_list<std::uint16_t> idList_;
};

#endif // ID_HANDLER_HPP