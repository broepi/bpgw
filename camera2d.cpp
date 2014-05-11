
#include <iostream>
#include <SDL2/SDL_opengl.h>
#include "camera2d.h"

using namespace std;

Camera2D::Camera2D (Display *display, Vector2D center)
	: display (display), center (center), pos (0,0), angle (0)
{
	dim = display->dim;
}

Camera2D::Camera2D (Vector2D pos, Vector2D dim, Vector2D center)
	: pos (pos), dim (dim), center (center), display (0), angle (0)
{
}

Camera2D::~Camera2D ()
{
}

void Camera2D::push ()
{
	glMatrixMode (GL_PROJECTION);
	glPushMatrix ();
	
	glTranslated (center.x*getDim().x, center.y*getDim().y, 0);
	glRotated (angle, 0, 0, 1);
	glTranslated (-pos.x, -pos.y, 0);
}

void Camera2D::pop ()
{
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();
}

Vector2D Camera2D::getDim ()
{
	if (display)
		return display->dim;
	else
		return dim;
}
