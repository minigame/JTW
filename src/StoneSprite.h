#ifndef __STONESPRITE_H
#define __STONESPRITE_H 1

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class StoneSprite: public cocos2d::Sprite
{
public:
	StoneSprite();
	~StoneSprite();
    bool init();
    CREATE_FUNC(StoneSprite);

public:


private:
    CC_SYNTHESIZE(cocos2d::PhysicsBody *, m_phyBox, PhyBox);
};

#endif
