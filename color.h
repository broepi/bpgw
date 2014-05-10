
#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>

class Color : public SDL_Color
{
public:
	Color ();
	Color (Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	Color (double r, double g, double b, double a = 1.0);
	~Color ();
};

#endif

