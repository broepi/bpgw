
#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable
{
public:
	int layer;
	
	Drawable () : layer (0) {}
	virtual void draw () = 0;
};

#endif

