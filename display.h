
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "vector2d.h"

class Display
{
public:
	Vector2D dim;
	SDL_Window *window;
	SDL_GLContext glContext;
	
	Display (Vector2D dim = Vector2D (800, 600), char *wndName = "My Window",
		bool resizeable = false);
	~Display ();
	void clear ();
	void present ();
};

#endif

