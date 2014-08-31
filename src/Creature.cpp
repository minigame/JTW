#include "Creature.h"
#include "DataConversion.h"


Creature::Creature()
{
	innerInit();
}

Creature::~Creature()
{
	Director::getInstance()->getScheduler()->unscheduleUpdate(this);
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

void Creature::resetRoleData(ROLE oldRole)
{
	m_status &= ~AttackAnimation;
	m_status &= ~Push;

	m_attackMaxCount = getMaxAttackCount();
	m_attackCount = 0;

	//��Ҫ��ȡ������Ҫ�������Ľ�ɫ������,������û�о�ֱ���½�
	std::map<ROLE,HpData>::iterator it = m_hpMap.find(m_currentRole);

	if(it == m_hpMap.end())
	{
		HpData data;
		data.currentBlood = 3;
		data.maxBlood = 3;
		data.beAttackedNum = 0;
		m_hpMap[m_currentRole] = data;
	}

	//Ȼ�����Ͻ�ɫ�Ƿ��Ѿ��ڱ��У�û�о������������½�һ��
	std::map<ROLE, HpData>::iterator iter = m_hpMap.find(oldRole);

	if(iter != m_hpMap.end())
	{
		HpData data;
		data.currentBlood = m_currentBlood;
		data.maxBlood = m_maxBlood;
		data.beAttackedNum = m_beAttackedNum;
		m_hpMap[oldRole] = data;
	}

	//��ȡҪ���ɵĽ�ɫ������
	m_currentBlood = m_hpMap[m_currentRole].currentBlood;
	m_maxBlood = m_hpMap[m_currentRole].maxBlood;
	m_beAttackedNum = m_hpMap[m_currentRole].beAttackedNum;

	updateBlood();
}

void Creature::innerInit()
{
	m_markContinueAttackFlag = false;
	m_attackMaxCount = DEFAULT_ATTACK_MAX_COUNT;
	m_attackCount = 0;
	m_jumpCount = 0;
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
	m_categorybitmask = 0;
	m_contacttestbitmask = 0;
	m_collisionbitmask = 0;

	//����״̬���¼�������
	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);

	m_verticalSpeed = DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("verticalSpeed"));
	m_horizontalSpeed = DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("horizontalSpeed"));
	m_attackBackImpulse_X = DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("AttackBackImpulse_X"));
	m_attackBackImpulse_Y = DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("AttackBackImpulse_Y"));
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
	onUpdateDir();
}

void Creature::setSpeed(Vec2 v)
{
	if(m_phyBox)
	{
		m_phyBox->setVelocity(v);
	}
}

void Creature::setSpeedX(float x)
{
	if (m_phyBox)
	{
		m_phyBox->setVelocity(Vec2(x, m_phyBox->getVelocity().y));
	}
}

void Creature::setSpeedY(float y)
{
	if (m_phyBox)
	{
		m_phyBox->setVelocity(Vec2(m_phyBox->getVelocity().x, y));
	}
}

void Creature::setPhyByArmatureContentSize(bool fourceChange)
{
	if(m_armature == NULL)
		return;

	Size size = m_armature->getContentSize();

	if (m_currentRole == Monkey)
		size.width = MONKEY_BODY_WIDTH;
	else if (m_currentRole == Pig)
		size.width = PIG_BODY_WIDTH;

	if (m_phyBox == NULL)
	{
		m_phyBox = cocos2d::PhysicsBody::createBox(size, MY_PHYSICSBODY_MATERIAL_DEFAULT);
		m_phyBox->setRotationEnable(false);//��ֹ��ת
		setBitmask();
		return;
	}
	
	if (fourceChange)
	{
		m_phyBox->removeAllShapes();
		m_phyBox->addShape(cocos2d::PhysicsShapeBox::create(size, MY_PHYSICSBODY_MATERIAL_DEFAULT));
		setBitmask();
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
	/*char buffer[256];
	itoa(m_phyBox->getVelocity().x, buffer, 10);
	std::string b = buffer;
	char bb[256];
	itoa(m_phyBox->getVelocity().y, bb, 10);
	b += ",";
	b += bb;
	b += "\n";
	LOGD(b.c_str(), NULL);*/


	//�����Զ�������״̬

	if (abs(m_phyBox->getVelocity().x) < TOO_SMALL_FLOAT && abs(m_phyBox->getVelocity().y) < TOO_SMALL_FLOAT && m_status == 0)
	{
		m_status = NoAnyAction;
	}
	else
	{
		m_status &= ~NoAnyAction;

		if (abs(m_phyBox->getVelocity().y) > TOO_SMALL_FLOAT)
		{
			m_status |= Fly;
		}
		
		//�洢Ӧ���еĵ��Ǳ��赲���ٶ�
		if (abs(m_phyBox->getVelocity().x) > TOO_SMALL_FLOAT && ((m_status & LeftWalk) || (m_status & RightWalk)))
		{
			if(lastPressedDirectionBtn == LeftWalk)
				m_lastHorSpeed = -m_horizontalSpeed;
			else if(lastPressedDirectionBtn == RightWalk)
				m_lastHorSpeed = m_horizontalSpeed;
		}
		else
		{
			//m_lastHorSpeed = 0;
		}
	}

	if (lastPressedDirectionBtn == LeftWalk)
	{
		changeDir(Left);
	}
	else if (lastPressedDirectionBtn == RightWalk)
	{
		changeDir(Right);
	}

	//�жϸ�������Ķ���
	if (m_status & Die)
	{
		//��������һ�ж������ȼ�
		updateAnimation(Die);
	}
	else if (m_status == NoAnyAction)
	{
		//վ�������
		updateAnimation(NoAnyAction);
	}
	else if (m_status & LeftWalk &&
		!(m_status & AttackAnimation)&&
		!(m_status & Fly) &&
		!(m_status & Push))
	{
		//����
		updateAnimation(LeftWalk);

	}
	else if (m_status & RightWalk &&
		!(m_status & AttackAnimation)&&
		!(m_status & Fly) &&
		!(m_status & Push))
	{
		//����
		updateAnimation(RightWalk);
	}
	else if (m_status & Fly && 
		!(m_status & AttackAnimation) &&
		!(m_status & Push))
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
		updateAnimation(Push);
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
					setSpeedX(-m_horizontalSpeed);

				lastPressedDirectionBtn = LeftWalk;
			}
			else
			{
				setSpeedX(0.0f);

				lastPressedDirectionBtn = NONESTATUS;
			}
			
		}
		else
		{
			m_status |= RightWalk;

			if (checkWalkable())
				setSpeedX(m_horizontalSpeed);

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
					setSpeedX(m_horizontalSpeed);

				lastPressedDirectionBtn = RightWalk;
			}
			else
			{
				setSpeedX(0.0f);
				lastPressedDirectionBtn = NONESTATUS;
			}	
		}
		else
		{
			m_status |= LeftWalk;

			if (checkWalkable())
				setSpeedX(-m_horizontalSpeed);

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

		if(m_markContinueAttackFlag)
			m_status |= ContinueAttack;

		if (!(m_status & AttackAnimation) &&
			!(m_status & Push))
		{
			//�������
			setSpeedX(0.0f);
			updateAnimation(Attack);
		}
	}
}

void Creature::jump(bool isCancel)
{
	if (!isCancel)
	{
		char buffer[265];
		itoa(m_jumpCount, buffer, 10);
		std::string b = buffer;
		b = "JumpCount:" + b + "\n";
		LOGD(b.c_str(), NULL);

		if(!(m_status & Fly) || 
			(m_status & Fly && m_currentRole == Monkey && m_jumpCount < 2))
		{
			if (m_currentRole == Monkey)
			{
				if (m_jumpCount == 0)
				{
					setSpeedY(m_verticalSpeed);
				}
				else
				{
					setSpeedY(m_verticalSpeed * 0.9);
				}
			}
			else
			{
				setSpeedY(m_verticalSpeed * 0.81);
			}
			m_jumpCount++;

			if (m_jumpCount == 1)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_JUMP);
			}
			else if (m_jumpCount == 2)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_MONKEY_2ND_JUMP);
			}
		}
	}
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
	case Push:
		return PUSH_TAG;
		break;
	default:
		return "";
		break;
	}
}

void Creature::updateAnimatonPlayStatus(STATUS s)
{
	//�����¼�����
	m_armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_4(Creature::onFrameEvent, this));

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
		m_armature->getAnimation()->playWithIndex(0, -1, 0);
		break;
	case Die:
		m_armature->getAnimation()->playWithIndex(0);
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
	ROLE oldRole = m_currentRole;
	m_currentRole = r;
	updateRoleName();

	if(r == Pig || r == Monkey || r == Puffer)
	{
		m_categorybitmask = PLAYER_CATEGORYBITMASK;
		m_contacttestbitmask = PLATER_CONTACTTESTBITMASK;
		m_collisionbitmask = PLAYER_COLLISIONBITMASK;
	}
	else if(r == Monster_1 || r == Monster_2)
	{
		m_categorybitmask = NPC_CATEGORYBITMASK;
		m_contacttestbitmask = NPC_CONTACTTESTBITMASK;
		m_collisionbitmask = NPC_COLLISIONBITMASK;
	}
	else
	{
		CCASSERT(0,"invaild role!");
	}

	onRoleChanged();
	resetRoleData(oldRole);
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
	m_jumpCount = 0;
	resumeSpeed();
}

void Creature::onCollisionHandle(Vec2 normal)
{
	if (normal.isZero())
		LOGD("All zero normal happens at Player.cpp 188");

	if (abs(normal.x) >= 0.5f)//��ЧֵĿǰֻ����1
	{
		setSpeedX(0.0f);

		if (normal.x > 0)//�����ײ
		{
			//clearLikeFlyStatus();
		}
		else if (normal.x < 0)//�ұ���ײ
		{
			//clearLikeFlyStatus();
			LOGD("right\n");
		}
	}
	else if (abs(normal.y) >= 0.5f)
	{
		setSpeedY(0.0f);

		if (normal.y > 0)//�±���ײ
		{
			LOGD("remove Jump now\n");
			clearFly();
			LOGD("remove Jump done\n");
		}
		else if (normal.y < 0)//�ϱ���ײ
		{
			LOGD("-1\n");
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
		if (abs(m_phyBox->getVelocity().x) <= TOO_SMALL_FLOAT && ((m_status & LeftWalk) || (m_status & RightWalk)))
		{
			LOGD("seperate\n");
			setSpeedX(m_lastHorSpeed);
			m_lastHorSpeed = 0;
		}

		if (normal.x > 0)//�����ײ
		{
			LOGD("seperate left\n");
			//clearLikeFlyStatus();
		}
		else if (normal.x < 0)//�ұ���ײ
		{
			LOGD("seperate right\n");
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
		setSpeedX(0.0f);
		return;
	}

	if (lastPressedDirectionBtn == LeftWalk)
	{
		setSpeedX(-m_horizontalSpeed);
	}
	else if (lastPressedDirectionBtn == RightWalk)
	{
		setSpeedX(m_horizontalSpeed);
	}
	else if (lastPressedDirectionBtn == NONESTATUS)
	{
		setSpeedX(0.0f);
	}
}

bool Creature::checkWalkable()
{
	if ((m_status & AttackAnimation) &&
		!(m_status & Fly))
	{
		return false;
	}
	else if ((m_status & Push))
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

int Creature::getBeAttackedNum() const   //�õ���ǰ�Ѿ����������ٴ�
{
	return m_beAttackedNum;
}


void Creature::addbeAttackedNum(int attackDirection, int num)    //�ܹ����Ĵ�����1
{
	m_beAttackedNum += num;

	LOGD("addbeAttackedNum");

	float impulse_X = m_attackBackImpulse_X;
	float impulse_Y = m_attackBackImpulse_Y;

	if (attackDirection & To_Left)
	{
		impulse_X = -impulse_X;
	}
	else
	{
		impulse_X = 0;
	}

	if (attackDirection & To_Down)
	{
		impulse_Y = -impulse_Y;
	}
	else
	{
		impulse_Y = 0;
	}

	if (attackDirection == 0)
	{
		impulse_X = 0;
		impulse_Y = -m_attackBackImpulse_Y * 2;
	}

	m_phyBox->applyImpulse(Vec2(impulse_X, impulse_Y));
	
	updateBlood();
}


void Creature::updateBlood()    //�������˵Ĵ���������Ѫ��
{
	int lostBlood = m_beAttackedNum / A2B;


	if (lostBlood >= m_maxBlood)   //����״̬
	{
		setBlood(0);
		onAttacked();
		dead();
	}
	else
	{
		setBlood(m_maxBlood - lostBlood);
		//û�����������Ҫ���
		m_armature->setColor(m_armature->getColor() + Color3B(50, 0, 0));

		//����Ѫui
		onAttacked();
	}
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

void Creature::dead()
{
	//��������������

	if (m_status & Die)
		return;

	//������������
	m_phyBox->setCategoryBitmask(DEATH_CATEGORYBITMASK);
	m_phyBox->setContactTestBitmask(DEATH_CONTACTTESTBITMASK);
	m_phyBox->setCollisionBitmask(DEATH_COLLISIONBITMASK);
	setSpeedY(m_verticalSpeed / 3);
	m_status |= Die;
	updateAnimation(Die);
	auto fade = FadeOut::create(1);
	CallFunc * func = CallFunc::create(CC_CALLBACK_0(Creature::deadCompleted, this));
	Sequence * sequenece = Sequence::create(fade, func, NULL);
	m_phyBox->getNode()->runAction(sequenece);
}

void Creature::setBitmask()
{
	m_phyBox->setCategoryBitmask(m_categorybitmask);
	m_phyBox->setContactTestBitmask(m_contacttestbitmask);
	m_phyBox->setCollisionBitmask(m_collisionbitmask);
}

void Creature::onFrameEvent(cocostudio::Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
}

void Creature::beginAttack()
{
	++m_attackCount;

	if (m_currentRole == Pig)
	{
		if (m_attackCount < getMaxAttackCount())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_PIG_FIGHT_LIGHT);
		}
		else if (m_attackCount == getMaxAttackCount())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_PIG_FIGHT_HEAVY);
		}
	}
	else if (m_currentRole == Monkey)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_MONKEY_FIGHT);
	}
}

int Creature::getMaxAttackCount() const
{
	return DEFAULT_ATTACK_MAX_COUNT;
}

void Creature::beginMarkContinueAttack()
{
	m_markContinueAttackFlag = true;
	m_status &= ~ContinueAttack;
}

void Creature::EndMarkContinueAttack()
{
	m_markContinueAttackFlag = false;
	m_status &= ~ContinueAttack;
}

void Creature::dealNextAttack()
{
	//��������û�������ֵ�����ڹ��������а��¹������������������
	if(m_attackCount < m_attackMaxCount && (m_status & ContinueAttack))
	{


	}
	else
	{
		m_status &= ~AttackAnimation;
		m_armature->getAnimation()->stop();
		m_attackCount = 0;
		resumeSpeed();
	}
}

void Creature::onRoleChanged()
{

}



