#ifndef CLICKABLE_UI_HPP
#define CLICKABLE_UI_HPP

#include "UserInterface.hpp"

class ClickableUI : public UserInterface {
public:
	ClickableUI( const std::vector<texInfo>& info )
		: UserInterface( info )
		, bMouseOn_( false )
		, bLbtnDown_( false ) {}
	virtual ~ClickableUI( ) {}

	virtual void update( ) override;
	virtual void render( HDC hdc ) override;

	bool mouseOnCheck( );

	void mouseOn( );
	void mouseLbtnDown( );
	void mouseLbtnUp( );
	void mouseLbtnClicked( );

	virtual ClickableUI* clone( ) override {
		return new ClickableUI{ *this };
	}

private:
	bool bMouseOn_;
	bool bLbtnDown_;
};

#endif // CLICKABLE_UI_HPP