#include "BridgeSprite.h"


BridgeSprite::BridgeSprite()
{
	m_phyBox = NULL;
	m_bridge = NULL;

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
	m_zhou->setPosition(Vec2(0.0f, -200.0f));

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
	
	//m_bridge->setRotation(-22.5);
	//m_phyBox->setRotationOffset(-22.5);

	//m_bridge->setRotation(-22.5);
	//m_phyBox->setRotationOffset(-22.5);

	//Vec2 pos = m_bridge->getPosition();
	//Size s = m_bridge->getContentSize();
	//m_bridge->setPosition(pos + Vec2(0.0f, -0.5f*s.height));
	//m_phyBox->setPositionOffset(pos + Vec2(0.0f, -0.5f*s.height));
	////m_phyBox->setPositionOffset
	//m_bridge->setRotation(-45);
	//m_phyBox->setRotationOffset(-45);
	//pos = m_bridge->getPosition();
	//m_bridge->setPosition(pos + Vec2(-0.5f*s.height*cosf(45)-20.0f,0.5f*s.height*sinf(45)-20.0f));
	//m_phyBox->setPositionOffset(pos + Vec2(-0.5f*s.height*cosf(45)-20.0f,0.5f*s.height*sinf(45)-20.0f));
	
	this->schedule(schedule_selector(BridgeSprite::rotate),1.0f);

	Director::getInstance()->getScheduler()->unschedule(schedule_selector(BridgeSprite::onCollisionHandle), this);
}

void BridgeSprite::rotate(float dt)
{
	if(dt<9)
	{
		Vec2 pos;
	Size s = m_bridge->getContentSize();
	Vec2 zhouPos;
	zhouPos = m_zhou->getPosition();
	Size zhouS = m_zhou->getContentSize();



	float fudu = dt*10.0f;   //旋转角度
	m_bridge->setRotation(-1.0*fudu);   //向右旋转
	m_phyBox->setRotationOffset(-1.0*fudu);   //向右旋转

	

	pos = m_bridge->getPosition();
	Vec2 bridgeBottomCenter = pos + Vec2(0.5f*s.height*sinf(fudu),-0.5f*s.height*cosf(fudu));
	Vec2 xiangliang = bridgeBottomCenter - zhouPos;

	m_bridge->setPosition(pos + xiangliang);
	m_phyBox->setPositionOffset(pos + xiangliang);
	}
	else
	{
		this->unschedule(schedule_selector(BridgeSprite::rotate));
	}
	
}

