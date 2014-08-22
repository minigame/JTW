#ifndef __BridgeSprite__H
#define __BBridgeSprite__H

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "DataConversion.h"
#include "ResourceMgr.h"
#include "Creature.h"
#include "PhyConst.h"
#include "Tag.h"

#define PAI 3.14159f

class BridgeSprite: public cocos2d::Sprite
{
public:
	BridgeSprite();
	~BridgeSprite();
    bool init();
    CREATE_FUNC(BridgeSprite);



public:
	cocos2d::PhysicsBody* m_phyBox;
	Sprite* m_bridge;
	Sprite* m_zhou;
	void onCollisionHandle(float dt);
	void setPhyBox();
	void rotate(float dt);
	int m_count;   //�����¼��ת�˶��ٴ�
	int m_dir;   //����  0�����ң�1������
};

#endif
