
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include "texture.h"

using namespace std;

class Game;

class TextureManager
{
public:
	struct stringComparator {
		bool operator() (char *a, char *b)
		{
			return strcmp (a, b) < 0;
		}
	};
	
	Game *game;
	char *resDir;
	map <char*, Texture*, stringComparator> textureMap;
	
	TextureManager (Game *game, char *resDir);
	~TextureManager ();
	Texture *getTexture (char *fileName);
};

#endif

