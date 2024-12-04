#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include "Object.hpp"
#include "Texture.hpp"

#include <string>
#include <vector>

class UserInterface : public Object {
public:
	UserInterface( const std::vector<texInfo>& info );
	virtual ~UserInterface( ) {}

	virtual void update( ) override {}
	virtual void render( HDC hdc ) override;

	virtual UserInterface* clone( ) override {
		return new UserInterface{ *this };
	}

protected:
	std::vector<Texture*> textures_;
	Texture* currTex_;
};

#endif 
// USERINTERFACE_HPP