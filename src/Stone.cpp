#include "Stone.h"

#include "PlayerSprite.h"
#include "PhyConst.h"

Stone::Stone()
{
    Gear();
    initWithFile("Stone");

    // 设置与stone相关的物理属性
	m_phyBox->setCategoryBitmask(STONE_CATEGORYBITMASK);
	m_phyBox->setContactTestBitmask(STONE_CONTACTTESTBITMASK);
	m_phyBox->setCollisionBitmask(STONE_COLLISIONBITMASK);

    m_sprite->setTag(STONE_TAG);
}

Stone::~Stone()
{

}





