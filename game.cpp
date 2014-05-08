
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include "display.h"

using namespace std;

Game::Game (Vector2D displayDim, char *wndName)
	: running (false)
{
	srand (time(0));
	
	if (SDL_Init (SDL_INIT_VIDEO) != 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (-1);
	}
	
	if (IMG_Init (IMG_INIT_PNG) == 0) {
		cerr << "IMG error: " << IMG_GetError () << endl;
		exit (-1);
	}
	
	display = new Display (displayDim, wndName);
	
	registerHandler (QUITEVENT, this);
}

Game::~Game ()
{
	unregisterHandler (QUITEVENT, this);
	
	delete display;
	
	IMG_Quit ();
	SDL_Quit ();
}

void Game::run ()
{
	SDL_Event event;
	
	running = true;
	while (running) {
		while (SDL_PollEvent (&event) == 1) {
			switch (event.type) {
			case SDL_QUIT:
				for (BpNode<EventHandler*> *i = handlerMap [QUITEVENT].first; i != 0; i = i->next)
				{
					i->val->onQuit ();
				}
				break;
			}
		}
		display->clear ();
		display->present ();
	}
}

void Game::registerHandler (Event event, EventHandler *handler)
{
	handlerMap [event].add (handler);
}

void Game::unregisterHandler (Event event, EventHandler *handler)
{
	handlerMap [event].rem (handler);
}

void Game::onQuit ()
{
	running = false;
}


