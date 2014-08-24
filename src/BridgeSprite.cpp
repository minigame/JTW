#include "BridgeSprite.h"


BridgeSprite::BridgeSprite()
{
	m_phyBox = NULL;
	m_bridge = NULL;
	m_zhou = NULL;
	m_count = 0;
	m_dir = 1;

}
BridgeSprite::~BridgeSprite()
{

}

bool BridgeSprite::init()
{
	if (!Sprite::init()) {
        return false;
    }

	m_bridge = Sprite::createWithSpriteFrame(ResourceMgr::getInstance()->getImage("bridge"));
	addChild(m_bridge);

	m_zhou = Sprite::createWithSpriteFrame(ResourceMgr::getInstance()->getImage("zhou"));
	addChild(m_zhou);
	m_zhou->setPosition(cocos2d::Vec2(0.0f, -200.0f));

	setPhyBox();
	
	return true;
   
}

void BridgeSprite::setPhyBox()
{
	m_phyBox = cocos2d::PhysicsBody::createBox(m_bridge->getContentSize(), MY_PHYSICSBODY_MATERIAL_DEFAULT);

	m_phyBox->setRotationEnable(false);
	m_phyBox->setDynamic(false);
	m_phyBox->setCategoryBitmask(GROUND_CATEGORYBITMASK);
	m_phyBox->setContactTestBitmask(GROUND_CONTACTTESTBITMASK);
	m_phyBox->setCollisionBitmask(GROUND_COLLISIONBITMASK);

	setTag(BRIDGE_TAG);

	this->setPhysicsBody(m_phyBox);
}


void BridgeSprite::onCollisionHandle(float dt)
{
	m_count = 0;

	this->schedule(schedule_selector(BridgeSprite::rotate), DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("bridgeTimePerRotate")));

	Director::getInstance()->getScheduler()->unschedule(schedule_selector(BridgeSprite::onCollisionHandle), this);
}

void BridgeSprite::rotate(float dt)
{
	m_count++;

	if(m_count<10)
	{
		Vec2 pos;
		Vec2 offsetV;
		Vec2 bridgeBottomCenter;
		Size bridgeSize = m_bridge->getContentSize();
		Vec2 zhouPos = m_zhou->getPosition();



		float angle = m_count*10.0f;   //旋转角度
		if(m_dir == 0)   //向右旋转
		{
			m_bridge->setRotation(angle);
			m_phyBox->setRotationOffset(angle);
			
			
			pos = m_bridge->getPosition();
			bridgeBottomCenter = pos + Vec2(-0.5f*bridgeSize.height*sinf(angle*PAI/180.0f),-0.5f*bridgeSize.height*cosf(angle*PAI/180.0f));
			offsetV = zhouPos - bridgeBottomCenter;
		}
		else   //向左旋转
		{
			m_bridge->setRotation(-1.0f*angle);
			m_phyBox->setRotationOffset(-1.0f*angle);
			
			
			pos = m_bridge->getPosition();
			bridgeBottomCenter = pos + Vec2(0.5f*bridgeSize.height*sinf(angle*PAI/180.0f),-0.5f*bridgeSize.height*cosf(angle*PAI/180.0f));
			offsetV = zhouPos - bridgeBottomCenter;
		}

		//float pai = 3.14159f;
		

		m_bridge->setPosition(pos + offsetV);
		m_phyBox->setPositionOffset(pos + offsetV);
	}
	else
	{
		this->unschedule(schedule_selector(BridgeSprite::rotate));
	}
	
}

