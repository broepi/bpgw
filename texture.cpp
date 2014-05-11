
#include <iostream>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "utils.h"

using namespace std;

Texture::Texture (Display *display, char *fileName, int cols, int rows)
	: display (display)
{
	SDL_Surface *surf = IMG_Load (fileName);
	
	if (surf == 0) {
		cerr << "IMG error: " << IMG_GetError () << endl;
		exit (-1);
	}
	
	loadSurface (surf);
	
	setTiling (cols, rows);
	
	SDL_FreeSurface (surf);
}

Texture::Texture (Display *display, unsigned char *data, Vector2D dim, int cols, int rows)
	: dim (dim)
{
	physDim = Vector2D (power2Expanded (dim.x), power2Expanded (dim.y));
	relDim = Vector2D (dim.x / physDim.x, dim.y / physDim.y);

	setTiling (cols, rows);
		
	glGenTextures (1, &glTexName);
	
	if (glTexName == 0) {
		cerr << "glGenTextures error" << endl;
		exit (-1);
	}
	
	glBindTexture (GL_TEXTURE_2D, glTexName);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, physDim.x, physDim.y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		data);
}

Texture::~Texture ()
{
	glDeleteTextures (1, &glTexName);
}

void Texture::setTiling (int cols, int rows)
{
	this->cols = cols;
	this->rows = rows;
	frameDim = Vector2D (dim.x / cols, dim.y / rows);
}

void Texture::loadSurface (SDL_Surface *surf)
{
	dim = Vector2D (surf->w, surf->h);
	physDim = Vector2D (power2Expanded (surf->w), power2Expanded (surf->h));
	relDim = Vector2D (dim.x / physDim.x, dim.y / physDim.y);
	
	SDL_Surface *tmpSurf = SDL_CreateRGBSurface (0, physDim.x, physDim.y, 32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		0x000000FF,
		0x0000FF00,
		0x00FF0000,
		0xFF000000);
#else
		0xFF000000,
		0x00FF0000,
		0x0000FF00,
		0x000000FF);
#endif
	
	if (tmpSurf == 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (-1);
	}

	SDL_SetSurfaceAlphaMod (surf, 0xff);
	SDL_SetSurfaceBlendMode (surf, SDL_BLENDMODE_NONE);
	
	SDL_Rect rect = {0, 0, dim.x, dim.y};
	SDL_BlitSurface (surf, &rect, tmpSurf, &rect);
	
	glGenTextures (1, &glTexName);
	
	if (glTexName == 0) {
		cerr << "glGenTextures error" << endl;
		exit (-1);
	}
	
	glBindTexture (GL_TEXTURE_2D, glTexName);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, physDim.x, physDim.y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		tmpSurf->pixels);

	SDL_FreeSurface (tmpSurf);
}

void Texture::draw (Vector2D pos, Vector2D scale, Vector2D center, Vector2D align, int frame,
	double angle, double alpha)
{
	int framex = frame % cols;
	int framey = frame / cols;
	
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glColor4d (1,1,1, alpha);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBindTexture (GL_TEXTURE_2D, glTexName);
	
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	
	glTranslated (pos.x, pos.y, 0.0);
	glTranslated (align.x*display->dim.x, align.y*display->dim.y, 0.0);
	glRotated (angle, 0, 0, 1);
	glScaled (scale.x, scale.y, 1.0);
	glTranslated (-center.x*frameDim.x, -center.y*frameDim.y, 0.0);
	
	glMatrixMode (GL_TEXTURE);
	glLoadIdentity ();
	
	glTranslated ((double)framex/cols, (double)framey/rows, 0.0);
	glScaled (1.0/cols, 1.0/rows, 1.0);
	
	glBegin (GL_QUADS);
	glTexCoord2d (0.0, 0.0);
	glVertex3d (0.0, 0.0, 0.0);
	glTexCoord2d (relDim.x, 0.0);
	glVertex3d (frameDim.x, 0.0, 0.0);
	glTexCoord2d (relDim.x, relDim.y);
	glVertex3d (frameDim.x, frameDim.y, 0.0);
	glTexCoord2d (0.0, relDim.y);
	glVertex3d (0.0, frameDim.y, 0.0);
	glEnd ();
	
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix();
}

