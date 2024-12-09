#include "LobbyScene.hpp"
#include "Background.hpp"
#include "WorldScene.hpp"

void LobbyScene::entry()
{
	auto background = new Background(L"Lobby Background", L"lobby/lobbyBackground.png");
	background->setObjName(L"Lobby Background");
	background->setObjPos(Vec2(640.f, 340.f));
	addObject(GROUP_TYPE::BACKGROUND, background);

	auto cupHead = new Background(L"Lobby character1", L"lobby/lobby1.png");
	cupHead->setObjName(L"Lobby character1");
	cupHead->setObjPos(Vec2(1000.f, 655.f));
	cupHead->setAlpha(50);
	addObject(GROUP_TYPE::BACKGROUND, cupHead);

	auto mugman = new Background(L"Lobby character2", L"lobby/lobby2.png");
	mugman->setObjName(L"Lobby character2");
	mugman->setObjPos(Vec2(1200.f, 655.f));
	mugman->setAlpha(50);
	addObject(GROUP_TYPE::BACKGROUND, mugman);
}
