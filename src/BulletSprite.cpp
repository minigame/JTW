#include "BulletSprite.h"
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
        return true;
    }
    return false;
}
