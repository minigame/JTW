#include "Creature.h"

Creature::Creature()
{
	m_Position = Vec2(0.0f, 0.0f);
	m_CurrentBlood = 0.0f;
	m_MaxBlood = 0.0f;
	m_dir = Right;
}

Creature::~Creature()
{
	//这块是不是要释放精灵动画
	if(m_armature)
	{
		delete m_armature;
		m_armature = NULL;
	}
}

Creature::Creature(float currentBlood, float maxBlood, DIR d)
{
	
	//m_vPosition = pos;
	if(currentBlood >= 0.0f)
		m_CurrentBlood = currentBlood;
	else
		m_CurrentBlood = 0.0f;

	if(maxBlood >= 0.0f)
		m_MaxBlood = maxBlood;
	else
		m_MaxBlood = 0.0f;

	m_dir = d;
	//m_bInScene = bs;
}

//void Creature::updatePosition(float dt)
//{
//	///////////////////这块是不是要判断位置的上下限；
//	//m_vPosition = m_vPosition + m_vXSpeed*dt + m_vYSpeed*dt + Vec2(0.0f, 0.5f*dt*dt);
//	m_Position = calcPosition(dt);
//}
//
//void Creature::updateSpeed(float dt)
//{
//	//m_vYSpeed = m_vYSpeed + Vec2(0, m_fGravityAcceleration*dt); 
//	m_speed = m_speed + m_acceleration*dt;
//}
//
//
//void Creature::setPosition(Vec2 pos)
//{
//	if(pos != m_Position)
//	{
//		m_Position = pos;
//	}
//}
//
//Vec2 Creature::calcPosition(float t)
//{
//	Vec2 pos;
//	pos = m_Position + m_speed*t + 0.5f*m_acceleration*t*t;
//	return pos;
//}

void Creature::setArmature(cocostudio::Armature* armature)
{
	if(m_armature != armature)
		m_armature = armature;
}


void Creature::setPhyBody(cocos2d::PhysicsBody* bodyBox)
{
	if(m_phyBox != bodyBox)
	{
		m_phyBox->release();
		m_phyBox = bodyBox;
	}	
}

void Creature::bindPhyBody()
{
	if(m_phyBox && m_armature)
		m_armature->setPhysicsBody(m_phyBox);
}


void Creature::setTag(int tag)
{
	if(m_armature)
		m_armature->setTag(tag);
}


void Creature::setArmatureWithAnimationName(char* name)
{
	if(m_armature)
	{
		delete m_armature;
		m_armature = NULL;
	}
	m_armature = cocostudio::Armature::create(name);
}

void Creature::setArmatureWithExportJsonFile(char* filename, char* armatureName)
{
	if(m_armature)
	{
		delete m_armature;
		m_armature = NULL;
	}
	cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(filename);
	m_armature = cocostudio::Armature::create(armatureName);
}

///////////这个没有写好
void Creature::setAnimationDirByDIR()
{
	if(m_dir == Right)   //正常播放行走动画
	{

	}
	else    //该生物现在向左行走，所以他的动画需要反向播放
	{
		//m_armature->setr
		//m_armature->setRotationSkewY
		//m_armature->setRotationY();
	}
}

void Creature::setDir(DIR d)
{
	m_dir = d;
}

void Creature::setSpeed(Vec2 v)
{
	if(m_armature && m_phyBox)
	{
		m_armature->getPhysicsBody()->setVelocity(v);
		//m_phyBox->setVelocity();
	}
}


void Creature::setPhyByArmatureContentSize()
{
	if(m_armature == NULL)
		return;

	Vec2 speed(0.0f, 0.0f);
	if(m_phyBox)
	{
		speed = getSpeed();
		m_phyBox->release();
		m_phyBox = NULL;
	}

	m_phyBox = cocos2d::PhysicsBody::createBox(m_armature->getContentSize(),PhysicsMaterial(0.0f, 0.0f, 0.0f));
	bindPhyBody();
	setSpeed(speed);
}


Vec2 Creature::getSpeed()
{
	if(m_phyBox)
		return m_phyBox->getVelocity();
	else
		return Vec2(0.0f, 0.0f);
}


