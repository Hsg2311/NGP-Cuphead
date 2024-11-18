#ifndef __BOSS1_SCENE_HPP
#define __BOSS1_SCENE_HPP

#include "Scene.hpp"

class Boss1_Scene : public Scene {
public:
	Boss1_Scene();
	virtual ~Boss1_Scene();

public:
	virtual void update() override;

public:
	virtual void Entry() override;
	virtual void Exit() override;

	/*void render( HDC hdc ) override;*/
};

#endif // __BOSS1_SCENE_HPP