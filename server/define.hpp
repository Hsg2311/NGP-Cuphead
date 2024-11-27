#ifndef DEFINE_HPP
#define DEFINE_HPP

#define SINGLETON(type)\
public:\
	type( const type& ) = delete;\
	type& operator=( const type& ) = delete;\
	type( type&& ) = delete;\
	type& operator=( type&& ) = delete;\
	\
	static type& getInst( ) {\
		static type inst;\
		return inst;\
	}\
	\
private:\
	type( );\
	~type( )

#endif // DEFINE_HPP