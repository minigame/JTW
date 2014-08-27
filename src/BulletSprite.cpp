#include "BulletSprite.h"
#include "Tag.h"
#include "Log.h"

using namespace cocostudio;
USING_NS_CC;

BulletSprite::BulletSprite()
{
    m_bulletId = 0;
    m_bullet   = NULL;
    m_normal.x = 0.0;
    m_normal.y = 0.0;
}

BulletSprite::~BulletSprite()
{
    if (m_bullet) {
        delete m_bullet;
    }
}

bool BulletSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    m_bullet = new Bullet(BulletType::BulletTypeMonkeyBo, Vec2(0.0, 0.0));
    if (m_bullet) {
        m_bullet->init();
        addChild(m_bullet->getItemArmature());
        m_bullet->getItemArmature()->getAnimation()->playWithIndex(0);
        if (m_bullet->getPhyBox()) {
            // 将phyBox绑定到sprite中，此时显示的图像受物理特性影响
            this->setPhysicsBody(m_bullet->getPhyBox());
        }
        this->setTag(ITEM_TAG);
        return true;
    }
    return false;
}

void BulletSprite::shoot(float speedX, float speedY)
{
    // 开启方向
    m_bullet->setSpeed(Vec2(speedX, speedY));
}

void BulletSprite::contactHandler()
{
    removeFromParentAndCleanup(true);
    LOGD("destory bullet now for edge");
}

//bool contactGroundHandler(BulletSprite * bullet, Sprite * edge)
//{
//    bullet->removeFromParentAndCleanup(true);
//    LOGD("destory bullet now for ground");
//    return false;
//}

