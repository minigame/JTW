#ifndef __STONESPRITE_H
#define __STONESPRITE_H 1

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

NS_CC_BEGIN

class StoneSprite: public Sprite
{
public:
	StoneSprite();
	~StoneSprite();
    bool init();
    CREATE_FUNC(StoneSprite);

    void move(float speed);
    void stop();

private:
    void moveHelper(float dt);
    float m_speed;
    CC_SYNTHESIZE(PhysicsBody *, m_phyBox, PhyBox);
};

NS_CC_END

#endif
