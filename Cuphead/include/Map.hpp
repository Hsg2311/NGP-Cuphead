#ifndef __MAP_HPP
#define __MAP_HPP

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
	Texture* _background;
};

#endif // __Map_HPP