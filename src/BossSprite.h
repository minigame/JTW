#ifndef BossSprite_h__
#define BossSprite_h__

#include "NPCSprite.h"

class BossSprite :
	public NPCSprite
{
public:
	BossSprite();
	~BossSprite();

	virtual bool init();
	CREATE_FUNC(BossSprite);

	virtual void AI(Point playerPos);
};

#endif 
