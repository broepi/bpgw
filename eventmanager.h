
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <set>
#include <map>
#include <SDL2/SDL.h>

using namespace std;

class EventManager
{
public:
	class Handler
	{
	public:
		virtual void onQuit (SDL_QuitEvent event) {}
		virtual void onWindow (SDL_WindowEvent event) {}
	};
	
	typedef set<Handler*> HandlerList;
	typedef map<Uint32, HandlerList> HandlerMap;
	typedef HandlerList::iterator HandlerListIter;
	
	SDL_Event event;
	HandlerMap handlerMap;

	EventManager ();
	~EventManager ();
	void registerHandler (Uint32 type, Handler *handler);
	void unregisterHandler (Uint32 type, Handler *handler);
	void update ();
};

typedef EventManager::Handler EventHandler;

#endif

