#include "WorldScene.hpp"
#include "Background.hpp"
#include "OverworldPlayer.hpp"

void WorldScene::entry( ) {
	auto background = new Background( L"World Background", L"overworld/world1_large_island_main_01.png" );
	background->setObjName( L"World Main Island" );
	background->setObjPos( Vec2( 640.f, 340.f ) );
	addObject( GROUP_TYPE::BACKGROUND, background );

	auto sweetHome = new BackgroundAnim( L"World Sweet Home", L"overworld/home_sweet_home.png", 0.065f, 3 );
	sweetHome->setObjName( L"World Sweet Home" );
	sweetHome->setObjPos( Vec2( 485.f, 655.f ) );
	addObject( GROUP_TYPE::BACKGROUND_ENTITY, sweetHome );

	auto info2 = std::vector<texInfo>( );
	info2.push_back( texInfo {
		.resKey = L"Idle_Down",
		.fileName = L"idle_down.png",
		.sliceSize = Vec2( 52.f, 96.f ),
		.duration = 0.11f,
		.frameCount = 5,
		} );
	info2.push_back( texInfo {
		.resKey = L"Idle_Up",
		.fileName = L"idle_up.png",
		.sliceSize = Vec2( 52.f, 82.f ),
		.duration = 0.095f,
		.frameCount = 6
	} );
	info2.push_back( texInfo {
		.resKey = L"Idle_Left",
		.fileName = L"idle_left.png",
		.sliceSize = Vec2( 62.f, 92.f ),
		.duration = 0.11f,
		.frameCount = 5
	} );
	info2.push_back( texInfo {
		.resKey = L"Idle_Right",
		.fileName = L"idle_right.png",
		.sliceSize = Vec2( 62.f, 92.f ),
		.duration = 0.11f,
		.frameCount = 5,
	} );
	info2.push_back( texInfo {
		.resKey = L"Idle_Left_Up",
		.fileName = L"idle_left_up.png",
		.sliceSize = Vec2( 56.f, 84.f ),
		.duration = 0.11f,
		.frameCount = 5,
	} );
	info2.push_back( texInfo {
		.resKey = L"Idle_Right_Up",
		.fileName = L"idle_right_up.png",
		.sliceSize = Vec2( 56.f, 84.f ),
		.duration = 0.11f,
		.frameCount = 5,
	} );
	info2.push_back( texInfo {
		.resKey = L"Idle_Left_Down",
		.fileName = L"idle_left_down.png",
		.sliceSize = Vec2( 60.f, 110.f ),
		.duration = 0.09f,
		.frameCount = 7,
	} );
	info2.push_back( texInfo {
		.resKey = L"Idle_Right_Down",
		.fileName = L"idle_right_down.png",
		.sliceSize = Vec2( 60.f, 110.f ),
		.duration = 0.09f,
		.frameCount = 7,
	} );
	info2.push_back( texInfo {
		.resKey = L"Walk_Up",
		.fileName = L"walk_up.png",
		.sliceSize = Vec2( 103.f, 114.f ),
		.duration = 0.065f,
		.frameCount = 12,
	} );
	info2.push_back( texInfo {
		.resKey = L"Walk_Down",
		.fileName = L"walk_down.png",
		.sliceSize = Vec2( 104.f, 110.f ),
		.duration = 0.065f,
		.frameCount = 13,
	} );
	info2.push_back( texInfo {
		.resKey = L"Walk_Left",
		.fileName = L"walk_left.png",
		.sliceSize = Vec2( 64.f, 90.f ),
		.duration = 0.07f,
		.frameCount = 11,
	} );
	info2.push_back( texInfo {
		.resKey = L"Walk_Right",
		.fileName = L"walk_right.png",
		.sliceSize = Vec2( 103.f, 110.f ),
		.duration = 0.07f,
		.frameCount = 11,
	} );
	info2.push_back( texInfo {
		.resKey = L"Walk_Left_Up",
		.fileName = L"walk_left_up.png",
		.sliceSize = Vec2( 64.f, 94.f ),
		.duration = 0.065f,
		.frameCount = 12,
		} );
	info2.push_back( texInfo {
		.resKey = L"Walk_Right_Up",
		.fileName = L"walk_right_up.png",
		.sliceSize = Vec2( 103.f, 114.f ),
		.duration = 0.065f,
		.frameCount = 12,
	} );
	info2.push_back( texInfo {
		.resKey = L"Walk_Left_Down",
		.fileName = L"walk_left_down.png",
		.sliceSize = Vec2( 62.f, 102.f ),
		.duration = 0.065f,
		.frameCount = 12,
	} );
	info2.push_back( texInfo {
		.resKey = L"Walk_Right_Down",
		.fileName = L"walk_right_down.png",
		.sliceSize = Vec2( 103.f, 110.f ),
		.duration = 0.065f,
		.frameCount = 12,
	} );

	auto player = new OverworldPlayer( info2 );
	player->setObjName( L"Overworld Player" );
	player->setObjPos( Vec2( 600.f, 800.f ) );
	addObject( GROUP_TYPE::PLAYER, player );

	Camera::getInst( ).setTarget( player );
}