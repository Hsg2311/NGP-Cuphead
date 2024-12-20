#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "Object.hpp"
#include "Texture.hpp"

#include <string>

class Background : public Object {
public:
	Background( const std::wstring& resKey, const std::wstring& fileName );
	virtual ~Background( ) {}

	virtual void update( ) override {}
	virtual void render( HDC hdc ) override;

	virtual Background* clone( ) override {
		return new Background{ *this };
	}

private:
	Texture* texture_;
};

class BackgroundAnim : public Object {
public:
	BackgroundAnim( const std::wstring& resKey, const std::wstring& fileName,
					float duration, UINT frameCount );
	virtual ~BackgroundAnim( ) {}

	virtual void update( ) override {}
	virtual void render( HDC hdc ) override;

	virtual BackgroundAnim* clone( ) override {
		return new BackgroundAnim{ *this };
	}
};

class BackgroundCharacter : public Object {
public:
	BackgroundCharacter( const std::wstring& resKey, const std::wstring& fileName, bool isCuphead );
	virtual ~BackgroundCharacter( ) {}

	virtual void update( ) override {}
	virtual void render( HDC hdc ) override;

	virtual BackgroundCharacter* clone( ) override {
		return new BackgroundCharacter{ *this };
	}

private:
	Texture* texture_;
	bool imCuphead_;
};

#endif // BACKGROUND_HPP