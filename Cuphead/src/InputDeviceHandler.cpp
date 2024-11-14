#include "InputDeviceHandler.hpp"

int g_arrVK[ static_cast<UINT>( InputData::EOE ) ] = {
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE
};

InputDeviceHandler::InputDeviceHandler( )
	: inputDataInfo_{ } {
	inputDataInfo_.reserve( static_cast<UINT>( InputData::EOE ) );
}

InputDeviceHandler::~InputDeviceHandler( )
{}

void InputDeviceHandler::init( ) {
	for ( UINT i = 0; i < static_cast<UINT>( InputData::EOE ); ++i ) {
		inputDataInfo_.emplace_back( KEY_STATE::NONE, false );
	}
}

void InputDeviceHandler::update( ) {
	// 현재 포커싱된 윈도우의 핸들을 가져옴
	HWND hWnd = GetFocus( );

	// 포커싱된 윈도우가 내 프로그램 윈도우 중 하나라면 키 이벤트 동작
	if ( hWnd ) {
		for ( UINT i = 0; i < static_cast<UINT>( InputData::EOE ); ++i ) {
			if ( GetAsyncKeyState( g_arrVK[ i ] ) & 0x8000 ) {
				if ( inputDataInfo_[ i ].isPressed ) {
					inputDataInfo_[ i ].state = KEY_STATE::HOLD;
				}
				else {
					inputDataInfo_[ i ].state = KEY_STATE::TAP;
				}
				inputDataInfo_[ i ].isPressed = true;
			}
			else {
				if ( inputDataInfo_[ i ].isPressed ) {
					inputDataInfo_[ i ].state = KEY_STATE::AWAY;
				}
				else {
					inputDataInfo_[ i ].state = KEY_STATE::NONE;
				}
				inputDataInfo_[ i ].isPressed = false;
			}
		}
	}
	else {
		for ( UINT i = 0; i < static_cast<UINT>( InputData::EOE ); ++i ) {
			inputDataInfo_[ i ].isPressed = false;

			if ( inputDataInfo_[ i ].state == KEY_STATE::TAP ||
				inputDataInfo_[ i ].state == KEY_STATE::HOLD ) {
				inputDataInfo_[ i ].state = KEY_STATE::AWAY;
			}
			else if ( inputDataInfo_[ i ].state == KEY_STATE::AWAY ) {
				inputDataInfo_[ i ].state = KEY_STATE::NONE;
			}
		}
	}
}