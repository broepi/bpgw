
#ifndef GAME_H
#define GAME_H

#include "eventhandler.h"
#include "vector2d.h"
#include "bpset.h"

class Display;

class Game : public EventHandler
{
public:
	enum Event {
		QUITEVENT,
		EVENTCOUNT
	};
	
	bool running;
	Display *display;
	BpSet<EventHandler*> handlerMap [EVENTCOUNT];
	
	Game (Vector2D displayDim = Vector2D (800, 600), char *wndName = "My Game");
	~Game ();
	void run ();
	void registerHandler (Event event, EventHandler *handler);
	void unregisterHandler (Event event, EventHandler *handler);
	void onQuit ();
};

#endif

