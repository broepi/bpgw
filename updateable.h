
#ifndef UPDATEABLE_H
#define UPDATEABLE_H

class Updateable
{
public:
	int order;
	
	Updateable () : order (0) {}
	virtual void update (double timeDelta) = 0;
};

#endif

