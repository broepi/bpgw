
#include <cstring>
#include <iostream>
#include "texturemanager.h"
#include "game.h"

using namespace std;

TextureManager::TextureManager (Game *game, char *resDir)
	: game (game), resDir (resDir)
{
}

TextureManager::~TextureManager ()
{
}

Texture *TextureManager::getTexture (char *fileName)
{
	if (textureMap.find (fileName) == textureMap.end ()) {
		char fullPath [strlen (resDir) + strlen(fileName) + 2];
		strcpy (fullPath, resDir);
		strcat (fullPath, "/");
		strcat (fullPath, fileName);
		return textureMap [fileName] = new Texture (game->display, fullPath);
	}
	else {
		return textureMap [fileName];
	}
}
