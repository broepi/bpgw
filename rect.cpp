
#include "rect.h"

Rect::Rect (double x, double y, double w, double h)
	: x (x), y (y), w (w), h (h)
{
}

Rect::Rect (Vector2D pos, Vector2D dim)
	: x (pos.x), y (pos.y), w (dim.x), h (dim.y)
{
}

Rect::Rect (const Rect& other)
	: x (other.x), y (other.y), w (other.w), h (other.h)
{
}

Rect::~Rect ()
{
}

Vector2D Rect::pos ()
{
	return Vector2D (x, y);
}

Vector2D Rect::dim ()
{
	return Vector2D (w, h);
}

