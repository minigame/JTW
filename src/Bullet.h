#ifndef Bullet_h__
#define Bullet_h__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "Item.h"

/*
 * @name: class Bullet: public Item
 * @desc: 子弹类，表示可以在空中飞行的各种具有碰撞属性的item
 * @data member:
 *
 * @function member:
 *
 */

// (density, friction, restitution)
// (密度，摩擦力，抓地力)
const cocos2d::PhysicsMaterial BULLET_PHYSICSBODY_MATERIAL_DEFAULT(0.0f, 0.0f, 0.0f);

enum BulletType
{
    BulletTypeNull,
    BulletTypeMonkeyBo,
	BulletTypeMonsterBo,
	BulletTypeBossBo
};

class Bullet: public Item
{
private:
    BulletType m_role;
    cocos2d::Vec2 m_speed;

public:
	Bullet();
	Bullet(BulletType type, cocos2d::Vec2 position);
	~Bullet();
    void init();

    void setSpeed(cocos2d::Vec2 speed);
    cocos2d::Vec2 getSpeed();

    void setSpeedY(float speed);
    void setSpeedX(float speed);

private:
	void updateBitmask();
};

#endif // Bullet_h__
