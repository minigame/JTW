#include "StoneSprite.h"
#include "ResourceMgr.h"
#include "PhyConst.h"
#include "Log.h"
#include "Tag.h"

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
    m_phyBox->setDynamic(false);

    // 设置与stone相关的物理属性
	m_phyBox->setCategoryBitmask(STONE_CATEGORYBITMASK);
	m_phyBox->setContactTestBitmask(STONE_CONTACTTESTBITMASK);
	m_phyBox->setCollisionBitmask(STONE_COLLISIONBITMASK);

    this->setPhysicsBody(m_phyBox);
    setTag(STONE_TAG);
    return true;
}

void StoneSprite::move(float speed)
{
    LOGD("stone is moving");
    //m_phyBox->applyImpulse(Vec2(speed, 0.0));
    m_phyBox->applyForce(Vec2(speed * 60, 0.0));
    m_speed = speed;
    // 立刻移动一次
    moveHelper(0);
    this->schedule(schedule_selector(StoneSprite::moveHelper), 1.0);
}

void StoneSprite::stop()
{
    LOGD("stone is stoped");
    m_speed = 0;
    m_phyBox->setDynamic(false);
    this->unschedule(schedule_selector(StoneSprite::moveHelper));
}

void StoneSprite::moveHelper(float dt)
{
    auto pos = getPosition();
    pos.x += m_speed;
    setPosition(pos);
}
