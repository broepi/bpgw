
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "vector2d.h"
#include "display.h"

class Texture
{
public:
	Display *display;
	Vector2D dim; //  dim of whole image
	Vector2D frameDim; // dim of one tile set piece
	Vector2D physDim; // pysical (power2) dim
	Vector2D relDim; // dim / frameDim
	int cols, rows; // tile set rows and cols
	GLuint glTexName;
	
	Texture (Display *display, char *fileName, int cols = 1, int rows = 1);
	Texture (unsigned char *data, Vector2D dim, int cols = 1, int rows = 1);
	~Texture ();
	void loadSurface (SDL_Surface *surf);
	void draw (
		Vector2D pos = Vector2D (0, 0),
		Vector2D scale = Vector2D (1, 1),
		Vector2D center = Vector2D (0, 0),
		Vector2D align = Vector2D (0, 0),
		int frame = 0, double angle = 0.0, double alpha = 1.0);
};

#endif

