#include "GateSprite.h"


GateSprite::GateSprite()
{
	m_phyBox = NULL;
	m_gate = NULL;
	m_zhou = NULL;
	m_dir = ZHOUDIR::Top;
	m_status = GateStatus::Line;
	m_totalMove = 0;
	m_detaMove = 5;
	m_MoveDir = 0;
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
	m_zhou->setPosition(cocos2d::Vec2(0.0f, 250.0f));

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
			m_zhou->setPosition(cocos2d::Vec2(0.0f,-250.0f));
		}
		else
		{
			///这块的数值要改
			m_zhou->setPosition(cocos2d::Vec2(0.0f,250.0f));
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


void GateSprite::run(float dt)
{
	if(m_status == GateStatus::Line)   //直线运动
	{
		runLine();
	}
	else   //弧线运动
	{
		runRotate();
	}
}


void GateSprite::startRun()
{
	this->schedule(schedule_selector(GateSprite::run), DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("GateTimePerMove")));
}


void GateSprite::runLine()
{
	int deta;
	if(m_MoveDir == 0)   //向左移动
	{
		deta = -1*m_detaMove;
		if((m_totalMove + deta) < -1*MoveRange)   //超过了最左边界
		{
			m_MoveDir = 1;
			m_totalMove -= deta;
			this->setPosition(this->getPosition() - cocos2d::Vec2(deta, 0.0f));
		}
		else   //继续往左移动deta
		{
			m_totalMove += deta;
			this->setPosition(this->getPosition() + cocos2d::Vec2(deta, 0.0f));
		}
	}
	else   //向右移动
	{
		deta = m_detaMove;
		if((m_totalMove + deta) > MoveRange)    //超过了最右边界
		{
			m_MoveDir = 0;
			m_totalMove -= deta;
			this->setPosition(this->getPosition() - cocos2d::Vec2(deta, 0.0f));
		}
		else   //继续往右边移动deta
		{
			m_totalMove += deta;
			this->setPosition(this->getPosition() + cocos2d::Vec2(deta, 0.0f));
		}
	}
}




void GateSprite::runRotate()
{
	int deta;
	cocos2d::Vec2 pos;
	cocos2d::Vec2 offsetV;
	cocos2d::Vec2 gateSupportPoint;
	cocos2d::Size gateSize = m_gate->getContentSize();
	cocos2d::Vec2 zhouPos = m_zhou->getPosition();
	if(m_MoveDir == 0)   //向左旋转
	{
		deta = -1*m_detaMove;
		if((m_totalMove + deta) < -1*MoveRange)  //超过了最左边界 ,,, 因此向右旋转
		{
			m_MoveDir = 1;
			m_totalMove -= deta;
		}
		else    //继续往左旋转deta
		{
			m_totalMove += deta;
		}

		m_gate->setRotation(m_totalMove);
		m_phyBox->setRotationOffset(m_totalMove);
		pos = m_gate->getPosition();

		if(m_dir == ZHOUDIR::Down)
		{
			gateSupportPoint = pos + cocos2d::Vec2(-0.5f*gateSize.height*sinf(m_totalMove*PAI/180.0f),-0.5f*gateSize.height*cosf(m_totalMove*PAI/180.0f));
		}
		else
		{
			gateSupportPoint = pos + cocos2d::Vec2(0.5f*gateSize.height*sinf(m_totalMove*PAI/180.0f),0.5f*gateSize.height*cosf(m_totalMove*PAI/180.0f));
		}

		offsetV = zhouPos - gateSupportPoint;
		m_gate->setPosition(pos + offsetV);
		m_phyBox->setPositionOffset(pos + offsetV);
	}
	else   //向右旋转
	{
		deta = m_detaMove;

		if((m_totalMove + deta) > MoveRange)  //超过了最右边界 ,,, 因此向左旋转
		{
			m_MoveDir = 0;
			m_totalMove -= deta;
		}
		else    //继续往右旋转deta
		{
			m_totalMove += deta;
		}

		m_gate->setRotation(m_totalMove);
		m_phyBox->setRotationOffset(m_totalMove);
		pos = m_gate->getPosition();

		if(m_dir == ZHOUDIR::Down)
		{
			gateSupportPoint = pos + cocos2d::Vec2(-0.5f*gateSize.height*sinf(m_totalMove*PAI/180.0f),-0.5f*gateSize.height*cosf(m_totalMove*PAI/180.0f));
		}
		else
		{
			gateSupportPoint = pos + cocos2d::Vec2(0.5f*gateSize.height*sinf(m_totalMove*PAI/180.0f),0.5f*gateSize.height*cosf(m_totalMove*PAI/180.0f));
		}

		offsetV = zhouPos - gateSupportPoint;
		m_gate->setPosition(pos + offsetV);
		m_phyBox->setPositionOffset(pos + offsetV);
	}
}

