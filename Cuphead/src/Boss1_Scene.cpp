#include "Boss1_Scene.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Monster.hpp"
#include "Core.hpp"
#include "CollisionHandler.hpp"
#include "InputDeviceHandler.hpp"
#include "func.hpp"
#include "SceneHandler.hpp"

Boss1_Scene::Boss1_Scene()
{}

Boss1_Scene::~Boss1_Scene()
{}

void Boss1_Scene::update() {
	Scene::update();

	if (KEY_TAP(InputData::Q)) {
		ChangeScene(SCENE_TYPE::SQUARE_SCENE);
		SceneHandler::GetInst().setSceneName(L"Square Scene");
	}
}

void Boss1_Scene::Entry() {

	SceneHandler::GetInst().setSceneName(L"Boss1 Scene");
	Object* map = new Map{};
	map->setObjName(L"Map");
	map->setObjPos(Vec2{ 0.f, 0.f });
	map->setObjScale(Vec2{ 1.f, 1.f });
	addObject(GROUP_TYPE::MAP, map);

	Object* obj = new Player{ };
	obj->setObjName(L"Player");
	obj->setObjPos(Vec2{ 640.f, 384.f });
	obj->setObjScale(Vec2{ 100.f, 100.f });
	addObject(GROUP_TYPE::PLAYER, obj);


	const auto monCount = 16;
	const auto monScale = 50.f;
	const auto moveDist = 25.f;
	const auto step = (Core::GetInst().getResolution().x - (2 * moveDist + monScale)) / (monCount - 1);

	for (auto i = 0; i < monCount; ++i) {
		Monster* mon = new Monster{ };
		mon->setObjName(L"Monster");
		mon->setObjPos(Vec2{ (moveDist + monScale / 2.f) + step * i, 50.f });
		mon->setCenterPos(mon->getObjPos());
		mon->setObjScale(Vec2{ monScale, monScale });
		mon->setMaxDistance(moveDist);
		mon->setSpeed(200.f);
		addObject(GROUP_TYPE::ENEMY, mon);
	}

	// 충돌 지정
	// 그룹 간의 충돌을 검사한다.
	CollisionHandler::GetInst().checkCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::ENEMY);
	CollisionHandler::GetInst().checkCollision(GROUP_TYPE::PLAYER_PROJECTILE, GROUP_TYPE::ENEMY);
}

void Boss1_Scene::Exit() {
	Scene::destroyObjGroupList();

	CollisionHandler::GetInst().reset();
}

//void Start_Scene::update( )
//{
//	Scene::update( );
//}
//

