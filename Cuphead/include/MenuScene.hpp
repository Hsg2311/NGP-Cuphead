#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "Scene.hpp"

class MenuScene : public Scene {
public:
	MenuScene( ) {}
	virtual ~MenuScene( ) {}

	virtual void update( ) override;
	virtual void entry( ) override;
	virtual void exit( ) override;
};

#endif // MENU_SCENE_HPP