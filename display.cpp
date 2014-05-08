
#include <iostream>
#include "display.h"

using namespace std;

Display::Display (Vector2D dim, char *wndName, bool resizeable)
	: dim (dim)
{
	SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 8);
	
	window = SDL_CreateWindow (wndName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		dim.x, dim.y, SDL_WINDOW_OPENGL | (resizeable ? SDL_WINDOW_RESIZABLE : 0));
	
	if (window == 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (-1);
	}
	
	glContext = SDL_GL_CreateContext (window);
	
	if (glContext == 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (-1);
	}
}

Display::~Display ()
{
	SDL_GL_DeleteContext (glContext);
	SDL_DestroyWindow (window);
}

void Display::clear ()
{
	glClearColor (0, 0, 0, 0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::present ()
{
	SDL_GL_SwapWindow (window);
}
