#include "Map.hpp"
#include "struct.hpp"
#include "Timer.hpp"
#include "InputDeviceHandler.hpp"
#include "Texture.hpp"
#include "ResourceHandler.hpp"
#include "func.hpp"
#include "SceneHandler.hpp"
#include "Core.hpp"
#define Width 1280
#define Height 768

Map::Map() {
	
	name = SceneHandler::GetInst().checkSceneName();

	if(name == L"Boss1 Scene"){
	_background = ResourceHandler::GetInst().LoadTexture(L"Map", L"/texture/overworld/map.png");
	}
}

Map::~Map(){
}

void Map::update() {
	

}

void Map::render(HDC hdc) {
	
	_player = SceneHandler::GetInst().GetCameraPos();
	
	_camera.x = _player.x - (Width / 2);
	_camera.y = _player.y - (Height / 2);
	
	_background->Draw(hdc, 0, 0, 1280, 768, _camera.x, _camera.y, 1280, 768); // 1280, 768 / 2560, 2839

	

}

