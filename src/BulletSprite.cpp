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
	m_type = BulletTypeNull;
	m_dir = 0;
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

	switch (m_type)
	{
	case BulletTypeNull:
		this->setTag(ITEM_TAG);
		m_bullet = new Bullet(BulletType::BulletTypeMonkeyBo, Vec2(0.0f, 0.0f));
		break;
	case BulletTypeMonkeyBo:
		this->setTag(ITEM_TAG);
		m_bullet = new Bullet(BulletType::BulletTypeMonkeyBo, Vec2(0.0f, 0.0f));
		break;
	case BulletTypeMonsterBo:
		this->setTag(MONSTER_BULLET_TAG);
		m_bullet = new Bullet(BulletType::BulletTypeMonsterBo, Vec2(0.0f, 0.0f));
		break;
	default:
		break;
	}

    if (m_bullet) 
	{
        m_bullet->init();
        addChild(m_bullet->getItemArmature());
        m_bullet->getItemArmature()->getAnimation()->playWithIndex(0);

        if (m_bullet->getPhyBox()) {
            // 将phyBox绑定到sprite中，此时显示的图像受物理特性影响
            this->setPhysicsBody(m_bullet->getPhyBox());
        }

        return true;
    }

    return false;
}

void BulletSprite::shoot(float speedX, float speedY)
{
    // 开启方向
    m_bullet->setSpeed(Vec2(speedX, speedY));

	if (speedX < -TOO_SMALL_FLOAT)
		m_dir |= To_Left;
	else if (speedX > TOO_SMALL_FLOAT)
		m_dir |= To_Right;

	if (speedY < -TOO_SMALL_FLOAT)
		m_dir |= To_Down;
	else if (speedY > TOO_SMALL_FLOAT)
		m_dir |= To_Up;

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BULLET);
}

void BulletSprite::contactHandler()
{
    removeFromParentAndCleanup(true);
    LOGD("destory bullet now for edge");
}


void BulletSprite::setType(BulletType _type)
{
	m_type = _type;
}

int BulletSprite::getDirection() const
{
	return m_dir;
}

