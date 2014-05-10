
#include "spritemanager.h"

bool SpriteManager::SpriteList::compare (Sprite *a, Sprite *b)
{
	return a->z < b->z;
}

void SpriteManager::SpriteList::add (Sprite *sprite)
{
	push_back (sprite);
}

void SpriteManager::SpriteList::sort ()
{
	list<Sprite*>::sort (compare);
}

SpriteManager::SpriteManager ()
{
}

SpriteManager::~SpriteManager ()
{
}

void SpriteManager::registerSprite (Sprite *sprite)
{
	sprites.add (sprite);
}

void SpriteManager::unregisterSprite (Sprite *sprite)
{
	sprites.remove (sprite);
}

void SpriteManager::update (double delta)
{
	for (SpriteListIter i = sprites.begin ();
		i != sprites.end ();
		i ++)
	{
		(*i)->update (delta);
	}
	sprites.sort ();
}

void SpriteManager::draw ()
{
	for (SpriteListIter i = sprites.begin ();
		i != sprites.end ();
		i ++)
	{
		(*i)->draw ();
	}
}

