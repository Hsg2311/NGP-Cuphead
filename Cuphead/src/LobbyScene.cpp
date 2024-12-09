#include "LobbyScene.hpp"
#include "Background.hpp"
#include "WorldScene.hpp"

void LobbyScene::entry()
{
	auto background = new Background(L"Lobby Background", L"lobby/lobbyBackground.png");
	background->setObjName(L"Looby");
	background->setObjPos(Vec2(640.f, 340.f));
	addObject(GROUP_TYPE::BACKGROUND, background);


	auto cupHead = new BackgroundAnim(L"Lobby character1", L"lobby/lobby1.png", 0.065f, 3);
	cupHead->setObjName(L"Lobby character1");
	cupHead->setObjPos(Vec2(485.f, 655.f));
	addObject(GROUP_TYPE::BACKGROUND_ENTITY, cupHead);

	auto mugman = new BackgroundAnim(L"Lobby character2", L"lobby/lobby2.png", 0.065f, 3);
	cupHead->setObjName(L"Lobby character1");
	cupHead->setObjPos(Vec2(485.f, 655.f));
	addObject(GROUP_TYPE::BACKGROUND_ENTITY, mugman);
}
