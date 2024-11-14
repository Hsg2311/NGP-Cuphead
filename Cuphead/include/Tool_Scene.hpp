#ifndef __TOOL_SCENE_HPP
#define __TOOL_SCENE_HPP

#include "Scene.hpp"

class Tool_Scene : public Scene {
public:
	Tool_Scene( );
	virtual ~Tool_Scene( );

public:
	virtual void update( ) override;

public:
	virtual void Entry( ) override;
	virtual void Exit( ) override;

private:

};

#endif // __TOOL_SCENE_HPP