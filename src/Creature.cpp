#include "Creature.h"
#include "DataConversion.h"

Creature::Creature()
{
	innerInit();
}

Creature::~Creature()
{
}

Creature::Creature(float currentBlood, float maxBlood, DIR d)
{
	innerInit();
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

void Creature::init(ROLE r, STATUS s)
{
	changeRole(r);
	m_status = s;
	updateAnimation(s);
}

void Creature::innerInit()
{
	m_currentBlood = 0.0f;
	m_maxBlood = 0.0f;
	m_dir = Right;
	m_armature = NULL;
	m_phyBox = NULL;
	m_status = 0;
	m_status = m_status | NoAnyAction;
	m_currentRole = NONE;
	m_lastHorSpeed = 0.0f;
	lastPressedDirectionBtn = NONESTATUS;
	m_currentBlood = 3;
	m_maxBlood = 3;
	m_beAttackedNum = 0;

	//����״̬���¼�������
	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);

	m_verticalSpeed = DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("verticalSpeed"));
	m_horizontalSpeed = DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("horizontalSpeed"));
}

void Creature::bindPhyBody(Node* parent)
{
	if (m_phyBox && parent)
		parent->setPhysicsBody(m_phyBox);
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

	//��remove
	Node * parent = NULL;

	if (m_armature)
	{
		parent = m_armature->getParent();
		
		if (parent)
		{
			m_armature->getAnimation()->stop();
			parent->removeChild(m_armature);
		}
	}
	
	m_armature = cocostudio::Armature::create(name);

	CCASSERT(m_armature, std::string("Cannot find animation" + std::string(name)).c_str());

	if (parent)
	{
		parent->addChild(m_armature);
	}

	setPhyByArmatureContentSize(isFourceChange);
	return true;
}

void Creature::setDir(DIR d)
{
	m_dir = d;
	CreatureDirData data;
	data.dir = m_dir;
	CallBackMgr::getInstance()->tigger(UPDATE_CREATURE_DIRECTION, &data);
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
		m_phyBox->setRotationEnable(false);//��ֹ��ת
		m_phyBox->setCategoryBitmask(PLAYER_CATEGORYBITMASK);
		m_phyBox->setContactTestBitmask(PLATER_CONTACTTESTBITMASK);
		m_phyBox->setCollisionBitmask(PLAYER_COLLISIONBITMASK);
		return;
	}
	
	if (fourceChange)
	{
		m_phyBox->removeAllShapes();
		m_phyBox->addShape(cocos2d::PhysicsShapeBox::create(m_armature->getContentSize(), MY_PHYSICSBODY_MATERIAL_DEFAULT));
		m_phyBox->setCategoryBitmask(PLAYER_CATEGORYBITMASK);
		m_phyBox->setContactTestBitmask(PLATER_CONTACTTESTBITMASK);
		m_phyBox->setCollisionBitmask(PLAYER_COLLISIONBITMASK);
	}
}


Vec2 Creature::getSpeed() const
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

void Creature::update(float dt)
{
	//char buffer[256];
	//itoa(m_status, buffer, 10);
	//std::string b = buffer;
	//b += "\n";
	//LOGD(b.c_str(), NULL);


	//�����Զ�������״̬

	if (m_phyBox->getVelocity().isZero() && m_status == 0)
	{
		m_status = NoAnyAction;
	}
	else
	{
		m_status &= ~NoAnyAction;

		if (m_phyBox->getVelocity().y != 0.0f)
		{
			m_status |= Fly;
		}
		
		if (m_phyBox->getVelocity().x < 0.0f)
		{
			changeDir(Left);
		}
		else if (m_phyBox->getVelocity().x > 0.0f)
		{
			changeDir(Right);
		}
	}

	////�����ٶȵĸ���
	//if (m_status & LeftWalk &&
	//	!(m_status & AttackAnimation))
	//{
	//	if (!(m_status & HaveLeftSpeed) &&
	//		!(m_status & ContactDuration))
	//	{
	//		//�������ٶ�û�м���
	//		setWalkSpeed(false, false);
	//	}
	//	else if (m_status & ContactDuration)
	//	{
	//		setWalkSpeed(false, false, false);
	//	}
	//}
	//else if (!(m_status & LeftWalk) &&
	//	m_status & HaveLeftSpeed)
	//{
	//	//�������ٶ���Ҫ����
	//	setWalkSpeed(false, true);
	//}

	//if (m_status & RightWalk &&
	//	!(m_status & AttackAnimation))
	//{
	//	//����ұ��ٶ�û�м���
	//	if (!(m_status & HaveRightSpeed) &&
	//		!(m_status & ContactDuration))
	//	{
	//		setWalkSpeed(true, false);
	//	}
	//	else if (m_status & ContactDuration)
	//	{
	//		m_phyBox->setVelocity(m_phyBox->getVelocity() + Vec2(m_horizontalSpeed, 0.0f));
	//	}
	//}
	//else if (!(m_status & RightWalk) &&
	//	m_status & HaveRightSpeed)
	//{
	//	//����ұ��ٶ���Ҫ����
	//	setWalkSpeed(true, true);
	//}


	//�жϸ�������Ķ���
	if (m_status == NoAnyAction)
	{
		//վ�������
		updateAnimation(NoAnyAction);
	}
	else if (m_status & LeftWalk &&
		!(m_status & AttackAnimation)&&
		!(m_status & Fly) &&
		!(m_status & PUSH))
	{
		//����
		updateAnimation(LeftWalk);

	}
	else if (m_status & RightWalk &&
		!(m_status & AttackAnimation)&&
		!(m_status & Fly) &&
		!(m_status & PUSH))
	{
		//����
		updateAnimation(RightWalk);
	}
	else if (m_status & Fly && 
		!(m_status & AttackAnimation) &&
		!(m_status & PUSH))
	{
		//�ɵ����
		updateAnimation(Fly);
	}
	else if (m_status & Hurt)
	{
		//���˱��
		
	}
	else if (!(m_status & Hurt))
	{
		//������
	}
	else if (m_status & Attack &&
		!(m_status & AttackAnimation) &&
		!(m_status & Fly))
	{
		//�ƶ�
		updateAnimation(PUSH);
	}
}

void Creature::walk(bool isForward, bool isCancel)
{
	if (isForward)
	{
		if (isCancel)
		{
			m_status &= ~RightWalk;

			if (m_status & LeftWalk)
			{
				if (checkWalkable())
					m_phyBox->setVelocity(Vec2(-m_horizontalSpeed, m_phyBox->getVelocity().y));

				lastPressedDirectionBtn = LeftWalk;
			}
			else
			{
				m_phyBox->setVelocity(Vec2(0.0f, m_phyBox->getVelocity().y));

				lastPressedDirectionBtn = NONESTATUS;
			}
			
		}
		else
		{
			m_status |= RightWalk;

			if (checkWalkable())
				m_phyBox->setVelocity(Vec2(m_horizontalSpeed, m_phyBox->getVelocity().y));

			lastPressedDirectionBtn = RightWalk;
		}
	}
	else
	{
		if (isCancel)
		{
			m_status &= ~LeftWalk;

			if (m_status & RightWalk)
			{
				if (checkWalkable())
					m_phyBox->setVelocity(Vec2(m_horizontalSpeed, m_phyBox->getVelocity().y));

				lastPressedDirectionBtn = RightWalk;
			}
			else
			{
				m_phyBox->setVelocity(Vec2(0.0f, m_phyBox->getVelocity().y));
				lastPressedDirectionBtn = NONESTATUS;
			}	
		}
		else
		{
			m_status |= LeftWalk;

			if (checkWalkable())
				m_phyBox->setVelocity(Vec2(-m_horizontalSpeed, m_phyBox->getVelocity().y));

			lastPressedDirectionBtn = LeftWalk;
		}
	}
}

void Creature::attack(bool isCancel)
{
	if (isCancel)
	{
		m_status &= ~Attack;
	}
	else
	{
		m_status |= Attack;

		if (!(m_status & AttackAnimation) &&
			!(m_status & PUSH))
		{
			//�������
			m_phyBox->setVelocity(Vec2(0.0f, m_phyBox->getVelocity().y));
			updateAnimation(Attack);
		}
	}
}

void Creature::jump(bool isCancel)
{
	if (!isCancel && !(m_status & Fly))
		m_phyBox->setVelocity(Vec2(m_phyBox->getVelocity().x, m_verticalSpeed));
}

void Creature::updateAnimation(STATUS s)
{
	if (m_currentRoleName.size() == 0)
		CCASSERT(0, "no role");
	
	std::string tag = getStatusTag(s);

	if (tag == "")
		CCASSERT(0, "no status");

	std::string animationName = m_currentRoleName + "_" + tag;

	if(setArmatureWithAnimationName(animationName.c_str()))
		updateAnimatonPlayStatus(s);
}

void Creature::updateRoleName()
{
	switch (m_currentRole)
	{
	case NONE:
		m_currentRoleName = "";
		break;
	case Monkey:
		m_currentRoleName = MONKEY_TAG;
		break;
	case Pig:
		m_currentRoleName = PIG_TAG;
		break;
	case Puffer:
		m_currentRoleName = PUFFER_TAG;
		break;
	case Monster_1:
		m_currentRoleName = MONSTER1_TAG;
		break;
	case Monster_2:
		m_currentRoleName = MONSTER2_TAG;
		break;
	default:
		CCASSERT(0, "unknow role tag");
		break;
	}
}

std::string Creature::getStatusTag(STATUS s)
{
	switch (s)
	{
	case NoAnyAction:
		return NOANYACTION_TAG;
		break;
	case LeftWalk:
	case RightWalk:
		return WALK_TAG;
		break;
	case Die:
		return DIE_TAG;
		break;
	case Attack:
		return ATTACK_TAG;
		break;
	case Fly:
		return FLY_TAG;
		break;
	case PUSH:
		return PUSH_TAG;
		break;
	default:
		return "";
		break;
	}
}

void Creature::updateAnimatonPlayStatus(STATUS s)
{
	switch (s)
	{
	case NoAnyAction:
		m_armature->getAnimation()->playWithIndex(0);
		m_armature->getAnimation()->pause();
		break;
	case LeftWalk:
	case RightWalk:
		m_armature->getAnimation()->playWithIndex(0);
		break;
	case Fly:
	case Die:
		m_armature->getAnimation()->playWithIndex(0, -1, 0);
		break;
	case Attack:
		m_armature->getAnimation()->playWithIndex(0, -1, 0);
		m_status |= AttackAnimation;
		m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Creature::onAttackEnd, this));
		break;
	default:
		break;
	}
}

void Creature::onAttackEnd(cocostudio::Armature * armatrue, cocostudio::MovementEventType type, const std::string& id)
{
	m_status &= ~AttackAnimation;
	resumeSpeed();
}

void Creature::setRole(ROLE r)
{
	m_currentRole = r;
	updateRoleName();
}

void Creature::changeRole(ROLE r)
{
	if (m_currentRole != r)
	{
		setRole(r);
	}
}

ROLE Creature::getRole() const
{
	return m_currentRole;
}

void Creature::clearFly()
{
	m_status &= ~Fly;
	resumeSpeed();
}

void Creature::onCollisionHandle(Vec2 normal)
{
	if (normal.isZero())
		LOGD("All zero normal happens at Player.cpp 188");

	if (abs(normal.x) >= 0.5f)//��ЧֵĿǰֻ����1
	{
		m_lastHorSpeed = m_phyBox->getVelocity().x;
		m_phyBox->setVelocity(Vec2(0.0f, m_phyBox->getVelocity().y));

		if (normal.x > 0)//�����ײ
		{
			//clearLikeFlyStatus();
		}
		else if (normal.x < 0)//�ұ���ײ
		{
			//clearLikeFlyStatus();
		}
	}
	else if (abs(normal.y) >= 0.5f)
	{
		setSpeed(Vec2(getSpeed().x, 0.0f));

		if (normal.y > 0)//�±���ײ
		{
			LOGD("remove Jump now\n");
			clearFly();
			LOGD("remove Jump done\n");
		}
		else if (normal.y < 0)//�ϱ���ײ
		{

		}
	}

	normal = Vec2(0.0f, 0.0f);
}

void Creature::changeDir(DIR r)
{
	if (m_dir != r)
		setDir(r);
}

void Creature::onCollisionEnd(Vec2 normal)
{
	if (normal.isZero())
		LOGD("All zero normal happens at Player.cpp 188");

	if (abs(normal.x) >= 0.5f)//��ЧֵĿǰֻ����1
	{
		if (m_phyBox->getVelocity().x == 0.0f)
			m_phyBox->setVelocity(Vec2(m_lastHorSpeed, m_phyBox->getVelocity().y));

		if (normal.x > 0)//�����ײ
		{
			//clearLikeFlyStatus();
		}
		else if (normal.x < 0)//�ұ���ײ
		{
			//clearLikeFlyStatus();
		}
	}
	else if (abs(normal.y) >= 0.5f)
	{
		if (normal.y > 0)//�±���ײ
		{
		}
		else if (normal.y < 0)//�ϱ���ײ
		{
		}
	}

	normal = Vec2(0.0f, 0.0f);
}

void Creature::resumeSpeed()
{
	if (!checkWalkable())
	{
		m_phyBox->setVelocity(Vec2(0.0f, m_phyBox->getVelocity().y));
		return;
	}

	if (lastPressedDirectionBtn == LeftWalk)
	{
		m_phyBox->setVelocity(Vec2(-m_horizontalSpeed, m_phyBox->getVelocity().y));
	}
	else if (lastPressedDirectionBtn == RightWalk)
	{
		m_phyBox->setVelocity(Vec2(m_horizontalSpeed, m_phyBox->getVelocity().y));
	}
	else if (lastPressedDirectionBtn == NONESTATUS)
	{
		m_phyBox->setVelocity(Vec2(0.0f, m_phyBox->getVelocity().y));
	}
}

bool Creature::checkWalkable()
{
	if ((m_status & AttackAnimation) &&
		!(m_status & Fly))
	{
		return false;
	}
	else if ((m_status & PUSH))
	{
		return false;
	}
	else
		return true;
}

void Creature::setBlood(int b)  //����Ѫ��
{
	if (b < 0 || b > m_maxBlood)
		return;

	m_currentBlood = b;
}

int Creature::getBlood() const //�õ���ǰ��Ѫ��
{
	return m_currentBlood;
}

void Creature::setBeAttackedNum(int num)   //���ñ������Ĵ���
{
	///////////Ӧ�û��и�����
	if (num < 0)
		return;

	m_beAttackedNum = num;
}

int Creature::getBeAttackedNum() const   //�õ���ǰ�Ѿ����������ٴ�
{
	return m_beAttackedNum;
}


void Creature::addbeAttackedNum()    //�ܹ����Ĵ�����1
{
	m_beAttackedNum++;

	updateBlood();
}


void Creature::updateBlood()    //�������˵Ĵ���������Ѫ��
{
	int lostBlood = m_beAttackedNum / A2B;


	if (lostBlood >= m_maxBlood)   //����״̬
	{
		setBlood(0);
	}
	else
	{
		setBlood(m_maxBlood - lostBlood);

		//����Ѫui
	}
}


void Creature::addbeAttackedNum(int addnum)    //�ܹ����Ĵ�����addnum
{
	m_beAttackedNum += addnum;

	updateBlood();
}

cocos2d::PhysicsBody* Creature::getPhyBody() const
{
	return m_phyBox;
}

void Creature::setMaxBlood(int blood)
{
	CCASSERT(blood > 0, "maxBlood should more than 0!");

	//for release
	if (blood < 0)
		return;
	//

	if (m_currentBlood > blood)
	{
		m_currentBlood = blood;
		m_maxBlood = blood;
	}
}

int Creature::getMaxBlood() const
{
	return m_maxBlood;
}

