
#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "game.h"
#include "color.h"

class Font
{
public:
	class GlyphBmp
	{
	public:
		GlyphBmp (int pitch, int width, int rows, int left, int top, int advance);
		~GlyphBmp ();
		
		int dataLen, pitch, width, rows;
		int left, top; // left and top bearing
		int advance;
		unsigned char *data;
	};
	
	Game *game;
	FT_Face face;
	GlyphBmp *asciiBitmaps [256-32];
	int maxHeight;
	int maxBearing;

	Font (Game *game, char *fileName, int ptSize);
	~Font ();
	Texture *createText (Display *display, char *text, Color color);
};

#endif
