#include "ElevatorSprite.h"
#include "ResourceMgr.h"

USING_NS_CC;

ElevatorSprite::ElevatorSprite()
{
	m_phyBox = NULL;
	m_speed = 0.0f;
	m_returnLength = 0.0f;
	m_originPosition = Vec2(0.0f, 0.0f);
	m_direction = UpAndDown;
}


ElevatorSprite::~ElevatorSprite()
{
}

void ElevatorSprite::setOriginPosition(Vec2 point)
{
	m_originPosition = point;
	this->setPosition(point);
}

Vec2 ElevatorSprite::getOriginPosition()
{
	return m_originPosition;
}

void ElevatorSprite::setReturnLength(float length)
{
	m_returnLength = length;
}

float ElevatorSprite::getReturnLength()
{
	return m_returnLength;
}

void ElevatorSprite::setSpeed(float speed)
{
	m_speed = speed;
}

float ElevatorSprite::getSpeed()
{
	return m_speed;
}

void ElevatorSprite::setDirection(Direction direction)
{
	m_direction = direction;
}

Direction ElevatorSprite::getDirection()
{
	return m_direction;
}

bool ElevatorSprite::init()
{
	if (!Sprite::init())
		return false;

	this->initWithSpriteFrame(ResourceMgr::getInstance()->getImage("Lift"));
	//this->setPosition(Point(200, 400));
	//m_originPosition = this->getPosition();
	//生成电梯的物理body
	if (m_phyBox == NULL)
	{
		m_phyBox = cocos2d::PhysicsBody::createBox(this->getContentSize(), MY_PHYSICSBODY_MATERIAL_FRICTION);
		m_phyBox->setRotationEnable(false);//禁止旋转
		m_phyBox->setDynamic(false);
		m_phyBox->setCategoryBitmask(ELEVATOR_CATEGORYBITMASK);
		m_phyBox->setContactTestBitmask(ELEVATOR_CONTACTTESTBITMASK);
		m_phyBox->setCollisionBitmask(ELEVATOR_COLLISIONBITMASK);
	}
	this->setPhysicsBody(m_phyBox);

	this->getScheduler()->scheduleUpdate(this, 0, false);

	return true;
}

void ElevatorSprite::update(float dt)
{
	Sprite::update(dt);
	Vec2 nowPosition = this->getPosition();
	if (m_direction == LeftAndRight)
	{
		if (abs(nowPosition.x - m_originPosition.x) > m_returnLength)
		{
			m_speed = m_speed * -1.0f;
		}
		this->setPosition(this->getPosition() + Vec2(dt * m_speed, 0));
	} 
	else if (m_direction == UpAndDown)
	{
		if (abs(nowPosition.y - m_originPosition.y) > m_returnLength)
		{
			m_speed = m_speed * -1.0f;
		}
		this->setPosition(this->getPosition() + Vec2(0, dt * m_speed));
	}
	
}