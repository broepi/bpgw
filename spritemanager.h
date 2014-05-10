
#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "sprite.h"

class SpriteManager
{
public:
	class SpriteList : public list<Sprite*>
	{
	public:
		static bool compare (Sprite *a, Sprite *b);
		void add (Sprite *sprite);
		void sort ();
	};
	
	typedef SpriteList::iterator SpriteListIter;
	
	SpriteList sprites;
	
	SpriteManager ();
	~SpriteManager ();
	void registerSprite (Sprite *sprite);
	void unregisterSprite (Sprite *sprite);
	void update (double delta);
	void draw ();
};

#endif

