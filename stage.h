
#ifndef STAGE_H
#define STAGE_H

class Stage
{
public:
	Stage ();
	~Stage ();
	virtual void enter () {}
	virtual void leave () {}
	virtual void update (double timeDelta) {}
	virtual void drawBg () {}
	virtual void drawFg () {}
};

#endif

