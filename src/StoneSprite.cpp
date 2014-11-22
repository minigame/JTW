#include "StoneSprite.h"
#include "ResourceMgr.h"
#include "PhyConst.h"
#include "Log.h"
#include "Tag.h"
#include "CommonMarco.h"

USING_NS_CC;
using namespace cocostudio;

StoneSprite::StoneSprite()
{
}

StoneSprite::~StoneSprite()
{

}

bool StoneSprite::init()
{
    if (!Sprite::initWithTexture(ResourceMgr::getInstance()->getImage("Stone"))) {
        return false;
    }

    // 石头的大小与图片相关
	m_phyBox = PhysicsBody::createBox(getContentSize(), STONE_PHYSICSBODY_MATERIAL_DEFAULT);
    m_phyBox->setDynamic(true);

    // 设置与stone相关的物理属性
	m_phyBox->setCategoryBitmask(STONE_CATEGORYBITMASK);
	m_phyBox->setContactTestBitmask(STONE_CONTACTTESTBITMASK);
	m_phyBox->setCollisionBitmask(STONE_COLLISIONBITMASK);
    m_phyBox->setRotationEnable(false);

    this->setPhysicsBody(m_phyBox);
    setTag(STONE_TAG);
    return true;
}

void StoneSprite::move(float speed)
{
    LOGD("stone is moving");
    //m_phyBox->applyImpulse(Vec2(speed, 0.0));
    //m_phyBox->applyForce(Vec2(speed * 60, 0.0));
    m_speed = speed * 3/5;
    // 立刻移动一次
    moveHelper(0);
    this->schedule(schedule_selector(StoneSprite::moveHelper), 1.0);
}

void StoneSprite::stop()
{
    LOGD("stone is stoped");
    m_speed = 0;
    //m_phyBox->setDynamic(false);
    this->unschedule(schedule_selector(StoneSprite::moveHelper));
}

void StoneSprite::moveHelper(float dt)
{
    auto pos = getPosition();
    pos.x += m_speed;
    setPosition(pos);
}

void StoneSprite::pigContactStoneHandler(float dt)
{
    // 只捕获水平方向上的速度
    if (abs(m_normal.y) < TOO_SMALL_FLOAT)
    {
        m_phyBox->setDynamic(true);
        float changeSpeed = m_speed;
        m_phyBox->setVelocity(Vec2(changeSpeed, 0.0));
    }
    // 否则不对石头进行影响
    else {
        m_phyBox->setVelocity(Vec2(0.0, 0.0));
        LOGD("stone: set dynamic false");
        m_phyBox->setDynamic(false);
    }
}

void StoneSprite::pigSeprateStoneHandler(float dt)
{
    printf("pig seprate (%f, %f)\n", m_normal.x, m_normal.y);
    if (abs(m_normal.y) < TOO_SMALL_FLOAT)
    {
        m_phyBox->setVelocity(Vec2(0.0, 0.0));
    }
    else {
        LOGD("stone: set dynamic true");
        m_phyBox->setDynamic(true);
    }
}

void StoneSprite::monkeyContactStoneHandler(float dt)
{
    m_phyBox->setDynamic(false);
}

void StoneSprite::monkeySeprateStoneHandler(float dt)
{
    m_phyBox->setDynamic(true);
}

void StoneSprite::stoneContactStoneHandler(float dt)
{
    m_phyBox->setVelocity(Vec2(0.0, 0.0));
}

void StoneSprite::stoneSeprateStoneHandler(float dt)
{
    m_phyBox->setVelocity(Vec2(0.0, 0.0));
}

