#include "Map.hpp"
#include "struct.hpp"
#include "Timer.hpp"
#include "InputDeviceHandler.hpp"
#include "Texture.hpp"
#include "ResourceHandler.hpp"
#include "func.hpp"

Map::Map() {
	CreateCollider();
	getCollider()->setScale(Vec2{ 50.f, 50.f });

	_background = ResourceHandler::GetInst().LoadTexture(L"Map", L"/texture/overworld/map.png");


}

Map::~Map()
{}

void Map::update() {

}

void Map::render(HDC hdc) {
	_background->Draw(hdc, 0, 0, 2048, 1847, 0, 0, 1280, 768);
	componentRender(hdc);
}

