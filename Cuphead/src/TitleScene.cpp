#include "TitleScene.hpp"
#include "Background.hpp"
#include "define.hpp"
#include "Core.hpp"
#include "Camera.hpp"
#include "UserInterface.hpp"
#include "BlinkingUI.hpp"

void TitleScene::update( ) {
	Scene::update( );
}

void TitleScene::entry( ) {
	auto background = new Background( L"Title", L"title/title_background.png" );
	background->setObjName( L"Title" );
	background->setObjPos( Vec2( 640.f, 360.f ) );
	addObject( GROUP_TYPE::BACKGROUND, background );

	auto backgroundAnim = new BackgroundAnim( L"Title_Cuphead_and_MugMan", L"title/title_cuphead_Mugman.png", 0.04f, 34 );
	backgroundAnim->setObjName( L"Title_Cuphead_and_MugMan" );
	backgroundAnim->setObjPos( Vec2( 640.f, 410.f ) );
	addObject( GROUP_TYPE::BACKGROUND, backgroundAnim );

	std::vector<texInfo> info;
	info.push_back( { L"Title_UI", L"title/press_any_key.png" } );

	auto ui = new BlinkingUI( info, true );
	ui->setObjName( L"Title_UI" );
	ui->setObjPos( Vec2( 640.f, 550.f ) );
	addObject( GROUP_TYPE::UI, ui );

	auto pos = Vec2( Core::getInst( ).getResolution( ) ) / 2.f;
	Camera::getInst( ).setLookAt( pos );
}

void TitleScene::exit( ) {
	Scene::destroyObjGroupList( );
}
