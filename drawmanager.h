
#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <list>
#include "drawable.h"

using namespace std;

class DrawManager
{
public:
	class DrawList : public list<Drawable*>
	{
	public:
		static bool compare (Drawable *a, Drawable *b);
		void add (Drawable *drawable);
		void sort ();
	};
	
	typedef DrawList::iterator DrawListIter;
	
	DrawList drawables;
	
	DrawManager ();
	~DrawManager ();
	void registerDrawable (Drawable *drawable);
	void unregisterDrawable (Drawable *drawable);
	void draw ();
};

#endif

