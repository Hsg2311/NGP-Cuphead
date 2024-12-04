#ifndef __DEFINE_HPP
#define __DEFINE_HPP

#define SINGLETON(type)	public:\
							type( const type& ) = delete;\
							type& operator=( const type& ) = delete;\
							type( type&& ) = delete;\
							type& operator=( type&& ) = delete;\
							\
							static type& getInst()\
							{\
								static type instance;\
								return instance;\
							}\
						private:\
							type( );\
							~type( )

#define fDT Timer::getInst().getFDT()
#define DT Timer::getInst().getDT()

#define KEY_CHECK( key, state ) InputDeviceHandler::getInst().getKeyState(key) == state
#define KEY_TAP( key ) KEY_CHECK( key, KEY_STATE::TAP )
#define KEY_HOLD( key ) KEY_CHECK( key, KEY_STATE::HOLD )
#define KEY_AWAY( key ) KEY_CHECK( key, KEY_STATE::AWAY )
#define KEY_NONE( key ) KEY_CHECK( key, KEY_STATE::NONE )
#define MOUSE_POS InputDeviceHandler::getInst().getMousePos()

enum class GROUP_TYPE {
	DEFAULT,
	BACKGROUND,
	BACKGROUND_ENTITY,
	PLAYER,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE,
	UI,

	EOE
};

enum class SCENE_TYPE {
	TITLE_SCENE,
	MENU_SCENE,
	TUTORIAL_SCENE,
	WORLD_SCENE,

	EOE
};

enum class PEN_TYPE {
	RED,
	GREEN,
	BLUE,

	EOE
};

enum class BRUSH_TYPE {
	HOLLOW,

	EOE
};

enum class EVENT_TYPE {
	CREATE_OBJECT,
	DESTROY_OBJECT,
	CHANGE_SCENE,

	EOE
};

#endif // __DEFINE_HPP