#include "Square_Scene.hpp"
#include "Object.hpp"
#include "OverWorldPlayer.hpp"
#include "Monster.hpp"
#include "Core.hpp"
#include "CollisionHandler.hpp"
#include "InputDeviceHandler.hpp"
#include "func.hpp"

#include "Texture.hpp"
#include "ResourceHandler.hpp"

Square_Scene::Square_Scene()
{
	/*auto tex = ResourceHandler::GetInst().LoadTexture(L"Player_Texture", L"/texture/idle/cuphead_idle.png");*/
	_background = ResourceHandler::GetInst().LoadTexture(L"Map", L"/texture/overworld/Large Island/Left/Main/world1_large_island_main_01.png");
	

}

Square_Scene::~Square_Scene()
{
}

void Square_Scene::update()
{
	Scene::update();
}

void Square_Scene::Entry()
{
	Object* obj = new OverWorldPlayer{};
	obj->getObjPos();
	obj->setObjName(L"OverWorldPlayer");
	obj->setObjPos(Vec2{ 640.f, 384.f });
	obj->setObjScale(Vec2{ 50.f, 50.f });
	addObject(GROUP_TYPE::PLAYER, obj);
	
}

void Square_Scene::Exit()
{
	Scene::destroyObjGroupList();
}

void Square_Scene::render(HDC hdc)
{
	//_background->Draw(hdc, 0, 0, 1240, 1884, 0, 0, 1240, 1884);
	
	
	Scene::render(hdc);
}