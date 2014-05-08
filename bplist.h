
#ifndef BPLIST_H
#define BPLIST_H

template <typename T>
class BpNode
{
public:
	BpNode<T> *next;
	BpNode<T> *prev;
	T val;
	
	BpNode (T val, BpNode *next = 0, BpNode *prev = 0)
		: next (next), prev (prev), val (val)
	{
	}
};

template <typename T>
class BpList
{
public:
	BpNode<T> *first;
	BpNode<T> *last;

	BpList ()
		: first (0), last (0)
	{
	}
	
	~BpList ()
	{
		clear ();
	}
	
	unsigned int length ()
	{
		BpNode<T> i = first;
		unsigned int n = 0;
		while (i != 0) {
			i = i->next;
			n ++;
		}
		return n;
	}
	
	BpNode<T> *findFirstNode (T val, BpNode<T> *from = 0)
	{
		if (from == 0) {
			from = first;
		}
		for (BpNode<T> *i = from; i != 0; i = i->next) {
			if (i->val == val) {
				return i;
			}
		}
		return 0;
	}
	
	BpNode<T> *findLastNode (T val, BpNode<T> *from = 0)
	{
		if (from == 0) {
			from = last;
		}
		for (BpNode<T> *i = from; i != 0; i = i->prev) {
			if (i->val == val) {
				return i;
			}
		}
		return 0;
	}
	
	BpNode<T> *getNthNode (unsigned int n)
	{
		BpNode<T> *i = first;
		while (i != 0 && n > 0) {
			i = i->next;
			n --;
		}
		return i;
	}
	
	T getNth (unsigned int n)
	{
		return getNthNode (n)->val;
	}
	
	void addFirst (T val)
	{
		BpNode<T> *newFirst = new BpNode<T> (val, first, 0);
		if (first == 0) {
			first = last = newFirst;			
		}
		else {
			first->prev = newFirst;
			first = newFirst;
		}
	}
	
	void addLast (T val)
	{
		BpNode<T> *newLast = new BpNode<T> (val, 0, last);
		if (last == 0) {
			last = first = newLast;
		}
		else {
			last->next = newLast;
			last = newLast;
		}
	}
	
	void insertBeforeNode (T val, BpNode<T> *nextNode)
	{
		BpNode<T> *newNode = new BpNode<T> (val, nextNode, nextNode->prev);
		if (nextNode == first) {
			first->prev = newNode;
			first = newNode;
		}
		else {
			nextNode->prev->next = newNode;
			nextNode->prev = newNode;
		}
	}
	
	void insertAfterNode (T val, BpNode<T> *prevNode)
	{
		BpNode<T> *newNode = new BpNode<T> (val, prevNode->next, prevNode);
		if (prevNode == last) {
			last->next = newNode;
			last = newNode;
		}
		else {
			prevNode->next->prev = newNode;
			prevNode->next = newNode;
		}
	}
	
	void insertAt (T val, unsigned int n)
	{
		insertBeforeNode (val, getNthNode (n));
	}
	
	void remFirst ()
	{
		if (first == 0) {
			return;
		}
		else if (first == last) {
			delete first;
			first = last = 0;
		}
		else {
			BpNode<T> *tmp = first->next;
			delete first;
			first = tmp;
			first->prev = 0;
		}
	}
	
	void remLast ()
	{
		if (last == 0) {
			return;
		}
		else if (last == first) {
			delete last;
			last = first = 0;
		}
		else {
			BpNode<T> *tmp = last->prev;
			delete last;
			last = tmp;
			last->next = 0;
		}
	}
	
	void remNode (BpNode<T> *node)
	{
		if (node == first) {
			first = first->next;
		}
		if (node == last) {
			last = last->prev;
		}
		if (node->next) {
			node->next->prev = node->prev;
		}
		if (node->prev) {
			node->prev->next = node->next;
		}
		delete node;
	}
	
	void remNth (unsigned int n)
	{
		remNode (getNthNode (n));
	}
	
	void remFirstVal (T val)
	{
		remNode (findFirstNode (val));
	}
	
	void remLastVal (T val)
	{
		remNode (findLastNode (val));
	}
	
	void remAllVals (T val)
	{
		BpNode<T> *tmp;
		for (BpNode<T> *i = first; i != 0; ) {
			if (i->val == val) {
				tmp = i;
				i = i->next;
				delete tmp;
			}
			else {
				i = i->next;
			}
		}
	}
	
	void clear ()
	{
		BpNode<T> *i = first;
		BpNode<T> *tmp;
		while (i != 0) {
			tmp = i;
			i = i->next;
			delete tmp;
		}
	}
};

#endif

