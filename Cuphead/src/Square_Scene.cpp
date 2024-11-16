#include "Square_Scene.hpp"
#include "Object.hpp"
#include "OverWorldPlayer.hpp"
#include "Map.hpp"
#include "Core.hpp"
#include "CollisionHandler.hpp"
#include "InputDeviceHandler.hpp"
#include "func.hpp"

#include "Texture.hpp"
#include "ResourceHandler.hpp"




Square_Scene::Square_Scene()
{


	
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
	Object* map = new Map{};
	map->setObjName(L"Map");
	map->setObjPos(Vec2{ 0.f, 0.f });
	map->setObjScale(Vec2{ 1.f, 1.f });
	addObject(GROUP_TYPE::MAP, map);

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

//void Square_Scene::render(HDC hdc)
//{
//	
//	
//	
//	Scene::render(hdc);
//}