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

    void monkeyContactStoneHandler(float dt);
    void monkeySeprateStoneHandler(float dt);
    
    void pigContactStoneHandler(float dt);
    void pigSeprateStoneHandler(float dt);
    
    void stoneContactStoneHandler(float dt);
    void stoneSeprateStoneHandler(float dt);
    float m_speed;

private:
    void moveHelper(float dt);
    CC_SYNTHESIZE(PhysicsBody *, m_phyBox, PhyBox);
    CC_SYNTHESIZE(Vec2, m_normal, Normal);
};

NS_CC_END

#endif
