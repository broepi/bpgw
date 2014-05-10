
#include "camera2d.h"

Camera2D::Camera2D (Vector2D center, Rect screen)
	: center (center), screen (screen)
{
}

Camera2D::~Camera2D ()
{
}

Vector2D Camera2D::worldToScreen (Vector2D v)
{
	return v - center + screen.dim ()/2 + screen.pos ();
}

