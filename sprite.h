
#ifndef SPRITE_H
#define SPRITE_H

#include <list>
#include "drawable.h"
#include "updateable.h"
#include "texture.h"
#include "vector2d.h"
#include "camera2d.h"

using namespace std;

class Game;

class Sprite : public Drawable, public Updateable
{
public:
	Game *game;
	Texture *tex;
	Camera2D *cam;
	Vector2D pos, scale, center, align;
	int frame;
	double angle;
	double alpha;
	Vector2D vel;
	Vector2D acc;
	
	Sprite (Game *game, Texture *tex = 0, Camera2D *cam = 0);
	Sprite (Game *game, char *texFileName, Camera2D *cam = 0);
	~Sprite ();
	void update (double timeDelta);
	void draw ();
};

#endif

