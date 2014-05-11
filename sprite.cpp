
#include <iostream>
#include "sprite.h"
#include "game.h"
#include "drawmanager.h"
#include "updatemanager.h"
#include "texturemanager.h"

using namespace std;

Sprite::Sprite (Game *game, Texture *tex, Camera2D *cam)
	: game (game), tex (tex), cam (cam), pos (0, 0), scale (1, 1), center (0, 0), align (0, 0),
	vel (0, 0), acc (0, 0), angle (0), alpha (1), frame (0)
{
	game->updateMan->registerUpdateable (this);
	game->drawMan->registerDrawable (this);
}

Sprite::Sprite (Game *game, char *texFileName, Camera2D *cam)
	: game (game), tex (0), cam (cam), pos (0, 0), scale (1, 1), center (0, 0), align (0, 0),
	vel (0, 0), acc (0, 0), angle (0), alpha (1), frame (0)
{
	tex = game->texMan->getTexture (texFileName);
	game->updateMan->registerUpdateable (this);
	game->drawMan->registerDrawable (this);
}

Sprite::~Sprite ()
{
	game->drawMan->unregisterDrawable (this);
	game->updateMan->unregisterUpdateable (this);
}

void Sprite::update (double timeDelta)
{
	vel += acc * timeDelta;
	pos += vel * timeDelta;
}

void Sprite::draw ()
{
	if (tex) {
		if (cam) cam->push ();
		tex->draw (pos, scale, center, align, frame, angle, alpha);
		if (cam) cam->pop ();
	}
}

