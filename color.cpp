
#include "color.h"

Color::Color ()
{
}

Color::Color (Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color (double r, double g, double b, double a)
{
	this->r = r*255;
	this->g = g*255;
	this->b = b*255;
	this->a = a*255;
}

Color::~Color ()
{
}

