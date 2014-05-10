
#include <iostream>
#include "font.h"
#include "utils.h"

using namespace std;

Font::GlyphBmp::GlyphBmp (int pitch, int width, int rows, int left, int top, int advance)
	: left(left), top(top), advance(advance)
{
	this->pitch = pitch;
	this->width = width;
	this->rows = rows;
	dataLen = pitch*rows;
	data = new unsigned char [dataLen];
}

Font::GlyphBmp::~GlyphBmp ()
{
	delete data;
}

Font::Font (Game *game, char *fileName, int ptSize)
	: game (game)
{
	if (FT_New_Face (game->freeType, fileName, 0, &face)) {
		cerr << "FT_New_Face error" << endl;
		exit (-1);
	}

	if (FT_Set_Char_Size (face, ptSize*64, ptSize*64, 0, 0)) {
		cerr << "FT_Set_Char_Size error" << endl;
		exit (-1);
	}

	maxBearing = 0;
	int minBearing = 0;
	int minBearingGlyphRows = 0;
	for (unsigned int c = 0x20; c <= 0xff; ++ c) {
		unsigned int i = c - 0x20;
		FT_UInt glyphIndex = FT_Get_Char_Index (face, c);

		if (FT_Load_Glyph (face, glyphIndex, FT_LOAD_DEFAULT)) {
			cerr << "FT_Load_Glyph error" << endl;
			exit (-1);
		}

		if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP) {
			if (FT_Render_Glyph (face->glyph, FT_RENDER_MODE_NORMAL)) {
				cerr << "FT_Render_Glyph error" << endl;
				exit (-1);
			}
		}
		
		FT_Bitmap *bmp = &face->glyph->bitmap;

		maxBearing = max (maxBearing, face->glyph->bitmap_top);
		if (
			face->glyph->bitmap_top < minBearing ||
			(face->glyph->bitmap_top == minBearing && minBearingGlyphRows < bmp->rows) )
		{
			minBearingGlyphRows = bmp->rows;
			minBearing = face->glyph->bitmap_top;
		}

		asciiBitmaps [i] = new GlyphBmp (
			bmp->pitch,
			bmp->width,
			bmp->rows,
			face->glyph->bitmap_left,
			face->glyph->bitmap_top,
			face->glyph->advance.x / 64);
		memcpy (asciiBitmaps [i]->data, bmp->buffer,
			bmp->pitch * bmp->rows * sizeof (unsigned char));
	}
	maxHeight = minBearingGlyphRows + maxBearing - minBearing;
}

Font::~Font ()
{
	for (unsigned int c = 0x20; c <= 0xff; ++ c) {
		unsigned int i = c - 0x20;
		delete asciiBitmaps [i];
	}
}

Texture *Font::createText (Display *display, char *text, Color color)
{
	int textWidth = 0;
	char *textPtr;
	
	textPtr = text;
	while (*textPtr) {
		unsigned int unicode = getchUtf8 ((unsigned char**)&textPtr);
		int index = unicode - '\x20';
		textWidth += asciiBitmaps [index]->advance;
	}
	
	int pw = power2Expanded (textWidth);
	int ph = power2Expanded (maxHeight);
	
	unsigned char *pixData = new unsigned char [pw * ph * 4];
	memset (pixData, 0, pw * ph * 4);
	unsigned int pen = 0;
	
	textPtr = text;
	while (*textPtr) {
		unsigned int unicode = getchUtf8 ((unsigned char**)&textPtr);
		int index = unicode - '\x20';
		GlyphBmp *bmp = asciiBitmaps [index];
		int glyphOffsx = bmp->left;
		int glyphOffsy = maxBearing - bmp->top;
		for (int row = 0; row < bmp->rows; row ++) {
			unsigned char *srcptr  = bmp->data + row * bmp->pitch;
			unsigned char *destptr = pixData + ((row + glyphOffsy) * pw + glyphOffsx + pen)*4;
			for (int col = 0; col < bmp->width; col ++) {
				destptr [0] = color.r;
				destptr [1] = color.g;
				destptr [2] = color.b;
				destptr [3] = color.a * srcptr [0] / 255;
				destptr += 4;
				srcptr ++;
			}
		}
		pen += bmp->advance;
	}
	
	Texture *texture = new Texture (pixData, textWidth, maxHeight);
	
	delete pixData;
	
	return texture;
}

