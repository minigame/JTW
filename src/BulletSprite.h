#ifndef __BulletSprite__H
#define __BulletSprite__H 1

#include "cocos2d.h"
#include "cocostudio.h"

class BulletSprite: public cocos2d::Sprite
{
public:
	BulletSprite();
	~BulletSprite();
    void init();
    CREATE_FUNC(BulletSprite)

public:
	Bullet * m_bullet;
	Vec2 m_normal;
};

#endif
