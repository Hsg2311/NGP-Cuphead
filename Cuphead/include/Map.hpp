#ifndef __MAP_HPP
#define __MAP_HPP

#include "Scene.hpp"
#include "Object.hpp"
#include <Windows.h>

class Texture;

class Map : public Object {
public:
	Map();
	virtual ~Map();

	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual Map* clone() override { return new Map{ *this }; }


public:
	Vec2 _player;
	Vec2 _camera;
	Texture* _background;
	std::wstring name;
};

#endif // __Map_HPP