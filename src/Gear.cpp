#include "Gear.h"

Gear::Gear()
{
    m_sprite = NULL;
}

Gear::~Gear()
{
}

void Gear::addPng2ArmatureWithFileName(char* name)
{
	m_sprite = cocos2d::Sprite::createWithSpriteFrame(ResourceMgr::getInstance()->getImage(name));

	m_phyBox = cocos2d::PhysicsBody::createBox(m_sprite->getContentSize(), MY_PHYSICSBODY_MATERIAL_DEFAULT);

	m_phyBox->setRotationEnable(false);
	m_phyBox->setDynamic(false);
	m_phyBox->setCategoryBitmask(GROUND_CATEGORYBITMASK);
	m_phyBox->setContactTestBitmask(GROUND_CONTACTTESTBITMASK);
	m_phyBox->setCollisionBitmask(GROUND_COLLISIONBITMASK);

    m_sprite->setPhysicsBody(m_phyBox);
}

void Gear::initWithFile(char* name)
{
	addPng2ArmatureWithFileName(name);
}

void Gear::init()
{

}

void Gear::setDynamic(bool b)
{
	if(m_phyBox)
	{
		m_phyBox->setDynamic(b);
	}
}

bool Gear::isDynamic()
{
	if(m_phyBox)
	{
		return m_phyBox->isDynamic();
	}

	return true;
}

void Gear::setPos(cocos2d::Vec2& v)
{
    if (m_sprite)
    {
        m_sprite->setPosition(v);
    }
}
