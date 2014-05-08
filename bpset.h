
#ifndef BPSET_H
#define BPSET_H

#include "bplist.h"

template <typename T>
class BpSet : public BpList<T>
{
public:
	bool includes (T val)
	{
		return this->findFirstNode (val) != 0;
	}
	
	void add (T val)
	{
		if (!includes (val)) {
			this->addLast (val);
		}
	}
	
	void rem (T val)
	{
		this->remFirstVal (val);
	}
};

#endif

