#ifndef __BulletSprite__H
#define __BulletSprite__H 1

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "Bullet.h"

class BulletSprite: public cocos2d::Sprite
{
public:
	BulletSprite();
	~BulletSprite();
    bool init();
    CREATE_FUNC(BulletSprite);

public:
    int      m_bulletId;
	Bullet * m_bullet;
    cocos2d::Vec2 m_normal;
};

#endif
