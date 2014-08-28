#include "StoneSprite.h"
#include "ResourceMgr.h"
#include "PhyConst.h"
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
	m_phyBox = PhysicsBody::createBox(getContentSize(), MY_PHYSICSBODY_MATERIAL_DEFAULT);

    // 设置与stone相关的物理属性
	m_phyBox->setCategoryBitmask(STONE_CATEGORYBITMASK);
	m_phyBox->setContactTestBitmask(STONE_CONTACTTESTBITMASK);
	m_phyBox->setCollisionBitmask(STONE_COLLISIONBITMASK);

    setTag(STONE_TAG);
    return true;
}
