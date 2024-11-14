#ifndef __Square_SCENE_HPP
#define __Square_SCENE_HPP

#include "Scene.hpp"

class Square_Scene : public Scene {
public:
	Square_Scene();
	virtual ~Square_Scene();

public:
	virtual void update() override;

public:
	virtual void Entry() override;
	virtual void Exit() override;

	virtual void render( HDC hdc ) override;

	Texture* _background;
};

#endif // __Square_SCENE_HPP