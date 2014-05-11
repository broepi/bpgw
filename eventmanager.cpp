
#include "eventmanager.h"

EventManager::EventManager ()
{
}

EventManager::~EventManager ()
{
}

void EventManager::registerHandler (Uint32 type, Handler *handler)
{
	handlerMap [type].insert (handler);
}

void EventManager::unregisterHandler (Uint32 type, Handler *handler)
{
	handlerMap [type].erase (handler);
}

void EventManager::update ()
{
	while (SDL_PollEvent (&event) == 1) {
		for (HandlerListIter i = handlerMap [event.type].begin ();
			i != handlerMap [event.type].end ();
			i ++)
		{
			switch (event.type) {
			case SDL_QUIT:
				(*i)->onQuit (event.quit);
				break;
			case SDL_WINDOWEVENT:
				(*i)->onWindow (event.window);
				break;
			case SDL_KEYDOWN:
				(*i)->onKeyDown (event.key);
				break;
			case SDL_KEYUP:
				(*i)->onKeyUp (event.key);
				break;
			}
		}
	}
}
