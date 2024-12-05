#ifndef __TITLE_SCENE_HPP
#define __TITLE_SCENE_HPP

#include "Scene.hpp"
#include "Animation.hpp"


class Title_Scene : public Scene {
public:
	Title_Scene();
	virtual ~Title_Scene();

public:
	virtual void update() override;

public:
	virtual void Entry() override;
	virtual void Exit() override;
	virtual void render(HDC) override;
	
private:
	Animator* animator_;
};

#endif // __START_SCENE_HPP