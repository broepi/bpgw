
#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <list>
#include "updateable.h"

using namespace std;

class UpdateManager
{
public:
	class UpdateList : public list<Updateable*>
	{
	public:
		static bool compare (Updateable *a, Updateable *b);
		void add (Updateable *updateable);
		void sort ();
	};
	
	typedef UpdateList::iterator UpdateListIter;
	
	UpdateList updateables;
	
	UpdateManager ();
	~UpdateManager ();
	void registerUpdateable (Updateable *updateable);
	void unregisterUpdateable (Updateable *updateable);
	void update (double timeDelta);
};

#endif

