
#include <iostream>
#include "display.h"
#include "game.h"

using namespace std;

Display::Display (Game *game, Vector2D dim, char *wndName, bool resizeable)
	: game (game), dim (dim)
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
	
	setBgColor (0, 0, 0);
	
	game->eventMan->registerHandler (SDL_WINDOWEVENT, this);
}

Display::~Display ()
{
	game->eventMan->unregisterHandler (SDL_WINDOWEVENT, this);
	
	SDL_GL_DeleteContext (glContext);
	SDL_DestroyWindow (window);
}

void Display::setBgColor (double r, double g, double b)
{
	glClearColor (r, g, b, 0);
}

void Display::activateScreenDrawMode ()
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, dim.x, dim.y, 0, -1, 1);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	glDisable (GL_DEPTH_TEST);
}

void Display::clear ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::present ()
{
	SDL_GL_SwapWindow (window);
}

void Display::drawPoint (Vector2D pos, Color color, int size)
{
	glDisable (GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize (1);
	glColor4ub (color.r, color.g, color.b, color.a);

	glBegin (GL_POINTS);
	
	for (int x=0; x<size; x++) {
		for (int y=0; y<size; y++) {
			glVertex3d (pos.x + x, pos.y + y, 0);
		}
	}
		
	glEnd ();
}

void Display::onWindow (SDL_WindowEvent event)
{
	switch (event.event) {
	case SDL_WINDOWEVENT_RESIZED:
		dim = Vector2D (event.data1, event.data2);
		glViewport (0, 0, dim.x, dim.y);
		break;
	}
}

