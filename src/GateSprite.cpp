#include "GateSprite.h"


GateSprite::GateSprite()
{
	m_phyBox = NULL;
	m_gate = NULL;
	m_zhou = NULL;
	m_dir = ZHOUDIR::Top;
	m_status = GateStatus::Line;
}
GateSprite::~GateSprite()
{

}


bool GateSprite::init()
{
	if (!Sprite::init()) {
        return false;
    }

	m_gate = Sprite::createWithSpriteFrame(ResourceMgr::getInstance()->getImage("gate"));
	addChild(m_gate);

	m_zhou = Sprite::createWithSpriteFrame(ResourceMgr::getInstance()->getImage("zhou"));
	addChild(m_zhou);



	//这块是要改动的，且这个是top的情况
	m_zhou->setPosition(cocos2d::Vec2(0.0f, -200.0f));

	setPhyBox();
	
	return true;
   
}


void GateSprite::setPhyBox()
{
	m_phyBox = cocos2d::PhysicsBody::createBox(m_gate->getContentSize(), MY_PHYSICSBODY_MATERIAL_DEFAULT);

	m_phyBox->setRotationEnable(false);
	m_phyBox->setDynamic(false);
	m_phyBox->setCategoryBitmask(GROUND_CATEGORYBITMASK);
	m_phyBox->setContactTestBitmask(GROUND_CONTACTTESTBITMASK);
	m_phyBox->setCollisionBitmask(GROUND_COLLISIONBITMASK);

	setTag(GATE_TAG);

	this->setPhysicsBody(m_phyBox);
}

void GateSprite::setZhouDir(ZHOUDIR dir)
{
	if(m_dir != dir)
	{
		m_dir = dir;

		if(dir == ZHOUDIR::Down)
		{
			///这块的数值要改
			m_zhou->setPosition(cocos2d::Vec2(0.0f,0.0f));
		}
		else
		{
			///这块的数值要改
			m_zhou->setPosition(cocos2d::Vec2(0.0f,0.0f));
		}
	}
}


void GateSprite::setGateRunStatus(GateStatus s)
{
	if(m_status != s)
	{
		m_status = s;
	}
}