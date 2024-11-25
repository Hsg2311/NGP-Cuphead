#ifndef BLINKING_UI_HPP
#define BLINKING_UI_HPP

#include "UserInterface.hpp"

class BlinkingUI : public UserInterface {
public:
	BlinkingUI( const std::vector<texInfo>& info, bool alpha )
		: UserInterface( info )
		, bAlpha_( alpha ) {}
	virtual ~BlinkingUI( ) {}

	virtual void update( ) override {}
	virtual void render( HDC hdc ) override;

	virtual BlinkingUI* clone( ) override {
		return new BlinkingUI( *this );
	}

private:
	bool bAlpha_;
	float accTime_ = 0.f;
};

#endif // !BLINKING_UI_HPP