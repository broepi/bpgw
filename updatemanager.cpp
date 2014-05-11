
#include "updatemanager.h"

bool UpdateManager::UpdateList::compare (Updateable *a, Updateable *b)
{
	return a->order < b->order;
}

void UpdateManager::UpdateList::add (Updateable *updateable)
{
	push_back (updateable);
}

void UpdateManager::UpdateList::sort ()
{
	list<Updateable*>::sort (compare);
}

UpdateManager::UpdateManager ()
{
}

UpdateManager::~UpdateManager ()
{
}

void UpdateManager::registerUpdateable (Updateable *updateable)
{
	updateables.add (updateable);
}

void UpdateManager::unregisterUpdateable (Updateable *updateable)
{
	updateables.remove (updateable);
}

void UpdateManager::update (double timeDelta)
{
	updateables.sort ();
	for (UpdateListIter i = updateables.begin ();
		i != updateables.end ();
		i ++)
	{
		(*i)->update (timeDelta);
	}
}

