#ifndef __BulletSprite__H
#define __BulletSprite__H

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "Bullet.h"
#include "CommonMarco.h"

enum BulletDirection
{
	To_Left = 1,
	To_Right = 2,
	To_Up = 4,
	To_Down = 8
};

class BulletSprite: public cocos2d::Sprite
{
public:
	BulletSprite();
	~BulletSprite();
    virtual bool init();
    CREATE_FUNC(BulletSprite);

public:
    void shoot(float speedX, float speedY = 0.0);
	void setType(BulletType _type);
	int  getDirection() const;

private:
    int      m_bulletId;
	Bullet * m_bullet;
    cocos2d::Vec2 m_normal;
	BulletType m_type;   //新加的，默认的是bullet。。。如果是monsterbo的话，就不是默认的
	int m_dir;

public:
    void contactHandler();

};

#endif
