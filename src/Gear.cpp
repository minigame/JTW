#include "Gear.h"


Gear::Gear()
{
}


Gear::~Gear()
{
}


void Gear::addPng2ArmatureWithFileName(char* name)
{
	cocos2d::Sprite* bitmap = cocos2d::Sprite::createWithSpriteFrame(ResourceMgr::getInstance()->getImage(name));
	//Size s = bitmap->getContentSize();
	if(m_armature)
	{
		m_armature->addChild(bitmap);
	}
	else
	{
		m_armature = cocostudio::Armature::create();
		m_armature->addChild(bitmap);
	}

	
	 m_phyBox = cocos2d::PhysicsBody::createBox(bitmap->getContentSize(), MY_PHYSICSBODY_MATERIAL_DEFAULT);
	 m_phyBox->setRotationEnable(false);
	 m_phyBox->setDynamic(false);
	 m_phyBox->setCategoryBitmask(GROUND_CATEGORYBITMASK);
	 m_phyBox->setContactTestBitmask(GROUND_CONTACTTESTBITMASK);
	 m_phyBox->setCollisionBitmask(GROUND_COLLISIONBITMASK);


	 m_armature->setPhysicsBody(m_phyBox);
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
	if(m_armature)
	{
		m_armature->setPosition(v);
	}
}





