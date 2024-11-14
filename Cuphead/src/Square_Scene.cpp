#include "Square_Scene.hpp"
#include "Object.hpp"
#include "Player.hpp"
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
	Object* obj = new Player{};
	obj->getObjPos();

	
}

void Square_Scene::Exit()
{
	Scene::destroyObjGroupList();
}

void Square_Scene::render(HDC hdc)
{
	_background->Draw(hdc, 0, 0, 1240, 1884, 0, 0, 1240, 1884);
	
	
	Scene::render(hdc);
}