
#include <iostream>
#include "drawmanager.h"

using namespace std;

bool DrawManager::DrawList::compare (Drawable *a, Drawable *b)
{
	return a->layer < b->layer;
}

void DrawManager::DrawList::add (Drawable *drawable)
{
	push_back (drawable);
}

void DrawManager::DrawList::sort ()
{
	list<Drawable*>::sort (compare);
}

DrawManager::DrawManager ()
{
}

DrawManager::~DrawManager ()
{
}

void DrawManager::registerDrawable (Drawable *drawable)
{
	drawables.add (drawable);
}

void DrawManager::unregisterDrawable (Drawable *drawable)
{
	drawables.remove (drawable);
}

void DrawManager::draw ()
{
	drawables.sort ();
	for (DrawListIter i = drawables.begin ();
		i != drawables.end ();
		i ++)
	{
		(*i)->draw ();
	}
}

