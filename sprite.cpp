
#include "sprite.h"

Sprite::Sprite (Texture *tex, Camera2D *cam)
	: tex (tex), cam (cam), pos (0, 0), scale (1, 1), center (0, 0), align (0, 0), vel (0, 0),
	acc (0, 0), angle (0), frame (0), z (0)
{
}

Sprite::~Sprite ()
{
}

void Sprite::update (double timeDelta)
{
	vel += acc * timeDelta;
	pos += vel * timeDelta;
}

void Sprite::draw ()
{
	if (cam) {
		tex->draw (cam->worldToScreen (pos), scale, center, align, frame, angle, alpha);
	}
	else {
		tex->draw (pos, scale, center, align, frame, angle, alpha);
	}
}

