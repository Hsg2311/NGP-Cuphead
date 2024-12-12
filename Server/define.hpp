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

enum class GROUP_TYPE {
	DEFAULT,
	BACKGROUND,
	BACKGROUND_ENTITY,
	CUPHEAD,
	MUGMAN,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE,
	UI,

	EOE
};

enum class SCENE_TYPE {
	MENU_SCENE,
	LOBBY_SCENE,
	WORLD_SCENE,

	EOE
};

enum class EVENT_TYPE {
	CREATE_OBJECT,
	DESTROY_OBJECT,
	CHANGE_SCENE,

	EOE
};

#endif // DEFINE_HPP