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

	//void render( HDC hdc );

	
};

#endif // __Square_SCENE_HPP