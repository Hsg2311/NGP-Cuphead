#ifndef __GLOBAL_FUNC_HPP
#define __GLOBAL_FUNC_HPP

#include <type_traits>
#include <ranges>
#include <algorithm>
#include <vector>
#include <map>

template<class T>
	requires std::is_pointer_v< std::remove_cvref_t<T> >
void safeDeleteVector( std::vector<T>& vec ) {
	std::ranges::for_each( vec, []( auto elem ) {
		delete elem;
	} );

	vec.clear( );
}

template<class T1, class T2>
	requires std::is_pointer_v< std::remove_cvref_t<T2> >
void safeDeleteMap( std::map<T1, T2>& map ) {
	std::ranges::for_each( map, []( auto& elem ) {
		delete elem.second;
	} );

	map.clear( );
}

#endif // __GLOBAL_FUNC_HPP