
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "eventmanager.h"
#include "vector2d.h"
#include "color.h"

class Game;

class Display : public EventHandler
{
public:
	Game *game;
	Vector2D dim;
	SDL_Window *window;
	SDL_GLContext glContext;
	
	Display (Game *game, Vector2D dim = Vector2D (800, 600), char *wndName = "My Window",
		bool resizeable = false);
	~Display ();
	void setBgColor (double r, double g, double b);
	void activateScreenDrawMode ();
	void clear ();
	void present ();
	void drawPoint (Vector2D pos, Color color);
	void onWindow (SDL_WindowEvent event);
};

#endif

