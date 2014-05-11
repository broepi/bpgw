
#ifndef camera_H
#define camera_H

#include "camera.h"
#include "vector2d.h"
#include "display.h"

class Camera2D : public Camera
{
public:
	Display *display; // optional
	Vector2D pos;
	Vector2D dim;
	Vector2D center; // 0..1
	double angle;

	Camera2D (Display *display, Vector2D center = Vector2D (0.5,0.5));
	Camera2D (Vector2D pos = Vector2D (0,0), Vector2D dim = Vector2D (800,600),
		Vector2D center = Vector2D (0.5,0.5));
	~Camera2D ();
	void push ();
	void pop ();
	Vector2D getDim ();
	//Vector2D worldToScreen (Vector2D p);
};

#endif

