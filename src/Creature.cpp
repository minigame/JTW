#include "Creature.h"

Creature::Creature()
{
	m_position = Vec2(0.0f, 0.0f);
	m_currentBlood = 0.0f;
	m_maxBlood = 0.0f;
	m_dir = Right;
	m_armature = NULL;
	m_phyBox = NULL;
}

Creature::~Creature()
{
}

Creature::Creature(float currentBlood, float maxBlood, DIR d)
{
	
	//m_vPosition = pos;
	if(currentBlood >= 0.0f)
		m_currentBlood = currentBlood;
	else
		m_currentBlood = 0.0f;

	if(maxBlood >= 0.0f)
		m_maxBlood = maxBlood;
	else
		m_maxBlood = 0.0f;

	m_dir = d;
	//m_bInScene = bs;
}

//void Creature::updatePosition(float dt)
//{
//	///////////////////这块是不是要判断位置的上下限；
//	//m_vPosition = m_vPosition + m_vXSpeed*dt + m_vYSpeed*dt + Vec2(0.0f, 0.5f*dt*dt);
//	m_position = calcPosition(dt);
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
//	if(pos != m_position)
//	{
//		m_position = pos;
//	}
//}
//
//Vec2 Creature::calcPosition(float t)
//{
//	Vec2 pos;
//	pos = m_position + m_speed*t + 0.5f*m_acceleration*t*t;
//	return pos;
//}

void Creature::setArmature(cocostudio::Armature* armature)
{
	if(m_armature != armature)
		m_armature = armature;
}


//void Creature::setPhyBody(cocos2d::PhysicsBody* bodyBox)
//{
//	if(m_phyBox != bodyBox)
//	{
//		m_phyBox = bodyBox;
//		bindPhyBody();
//	}	
//}

void Creature::bindPhyBody(Node* parent)
{
	if (m_phyBox && parent)
		parent->setPhysicsBody(m_phyBox);
}


void Creature::setTag(int tag)
{
	if(m_armature)
		m_armature->setTag(tag);
}


bool Creature::setArmatureWithAnimationName(const char* name)
{
	if(m_armature && m_armature->getName() == name)
		return false;

	bool isFourceChange = false;
	
	if (m_armature)
	{
		std::string newRoleName;
		int pos = std::string(name).find("_");
		CCASSERT(pos != std::string::npos, "role name is uncorrect!");
		newRoleName = std::string(name).substr(0, pos);

		std::string oldRoleName;
		pos = m_armature->getName().find("_");
		CCASSERT(pos != std::string::npos, "role name is uncorrect!");
		oldRoleName = m_armature->getName().substr(0, pos);

		if (newRoleName != oldRoleName)
			isFourceChange = true;
	}

	//先remove
	Node * parent = NULL;
	int zOrder = 0;

	if (m_armature)
	{
		parent = m_armature->getParent();
		
		if (parent)
		{
			zOrder = m_armature->getLocalZOrder();
			m_armature->getAnimation()->stop();
			parent->removeChild(m_armature);
		}
	}
	
	m_armature = cocostudio::Armature::create(name);

	CCASSERT(m_armature, std::string("Cannot find animation" + std::string(name)).c_str());

	if (parent)
	{
		parent->addChild(m_armature, zOrder);
	}

	setPhyByArmatureContentSize(isFourceChange);
	return true;
}

void Creature::setArmatureWithExportJsonFile(char* filename, char* armatureName)
{
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
		m_phyBox->setVelocity(v);
		//m_phyBox->setVelocity();
	}
}


void Creature::setPhyByArmatureContentSize(bool fourceChange)
{
	if(m_armature == NULL)
		return;

	if (m_phyBox == NULL)
	{
		m_phyBox = cocos2d::PhysicsBody::createBox(m_armature->getContentSize(), MY_PHYSICSBODY_MATERIAL_DEFAULT);
		m_phyBox->setRotationEnable(false);//禁止旋转
		return;
	}
	
	if (fourceChange)
	{
		m_phyBox->removeAllShapes();
		m_phyBox->addShape(cocos2d::PhysicsShapeBox::create(m_armature->getContentSize(), MY_PHYSICSBODY_MATERIAL_DEFAULT));
	}
}


Vec2 Creature::getSpeed()
{
	if(m_phyBox)
		return m_phyBox->getVelocity();
	else
		return Vec2(0.0f, 0.0f);
}

cocostudio::Armature * Creature::getArmature() const
{
	return m_armature;
}

DIR Creature::getDir() const
{
	return m_dir;
}


