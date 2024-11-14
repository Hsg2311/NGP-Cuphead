#include "Title_Scene.hpp"
#include "InputDeviceHandler.hpp"
#include "ResourceHandler.hpp"
#include "Texture.hpp"
#include "ResourceHandler.hpp"
#include <windows.h>

HWND hWnd;

Title_Scene::Title_Scene()
{
	animator_ = new Animator{ };
	auto tex2 = ResourceHandler::GetInst().LoadTexture(L"title_idle", L"/texture/title/title_cuphead.png");
	animator_->createAnimation(L"title_idle", tex2, Vec2{ 0.f, 0.f },
		Vec2{ 1093.f, 622.f }, Vec2{ 1093.f, 0.f }, 0.065f, 34);
	animator_->play(L"title_idle");
}

Title_Scene::~Title_Scene()
{}

void Title_Scene::update()
{
	Scene::update();
	if (animator_) {
		animator_->update();
	}

	if (KEY_TAP(InputData::ENTER)) {
		ChangeScene(SCENE_TYPE::START_SCENE);
	}
}

void Title_Scene::Entry()
{

}

void Title_Scene::Exit()
{
	
}

void Title_Scene::render(HDC hdc)
{

	auto tex1 = ResourceHandler::GetInst().LoadTexture(L"title_bg", L"/texture/title/title_background.png");

	tex1->Draw(hdc, 0, 0, 1280, 768, 0, 0, 1280, 720);
	Scene::render(hdc);
	if (animator_)
		animator_->render(hdc, Vec2{ 640.f, 460.f });

}