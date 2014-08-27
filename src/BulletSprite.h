#ifndef __BulletSprite__H
#define __BulletSprite__H

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
    void shoot(float speedX, float speedY = 0.0);

public:
    int      m_bulletId;
	Bullet * m_bullet;
    cocos2d::Vec2 m_normal;

	int type;   //�¼ӵģ�Ĭ�ϵ���bullet�����������monsterbo�Ļ����Ͳ���Ĭ�ϵ�
	void setType(int _type);

public:
    void contactHandler();
    /*static bool contactGroundHandler(BulletSprite * bullet, Sprite * edge);*/

};

#endif
