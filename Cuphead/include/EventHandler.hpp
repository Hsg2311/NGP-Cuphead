#ifndef __EVENT_HANDLER_HPP
#define __EVENT_HANDLER_HPP

#include "define.hpp"
#include <Windows.h>
#include <vector>

class Object;

struct Event {
	EVENT_TYPE eventType;
	DWORD_PTR wParam;
	DWORD_PTR lParam;
};

class EventHandler
{
	SINGLETON( EventHandler );

public:
	void update( );
	void excute( const Event& event );

public:
	void addEvent( const Event& event ) { events_.push_back(event); }

private:
	std::vector<Event> events_;
	std::vector<Object*> deadObjects_;
};

#endif // __EVENT_HANDLER_HPP