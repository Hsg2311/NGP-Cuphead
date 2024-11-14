#ifndef __START_SCENE_HPP
#define __START_SCENE_HPP

#include "Scene.hpp"

class Start_Scene : public Scene {
public:
	Start_Scene( );
	virtual ~Start_Scene( );

public:
	virtual void update( ) override;

public:
	virtual void Entry( ) override;
	virtual void Exit( ) override;

	//virtual void render( HDC hdc ) override;
};

#endif // __START_SCENE_HPP