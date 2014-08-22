#ifndef __BridgeSprite__H
#define __BBridgeSprite__H

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "Bridge.h"

class BridgeSprite: public cocos2d::Sprite
{
public:
	BridgeSprite();
	~BridgeSprite();
    bool init();
    CREATE_FUNC(BridgeSprite);



public:
	PhysicsBody* m_phyBox;
	Sprite* m_bridge;
	Sprite* m_zhou;
	void onCollisionHandle(float dt);
	void setPhyBox();
	void rotate(float dt);
};

#endif
