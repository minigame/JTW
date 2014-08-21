#include "Player.h"
#include "PhyConst.h"

Player::Player()
{
	m_currentRole = ROLE::Monkey;
	setDir(NoMoveRight);
	f_verticalSpeed = DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("verticalSpeed"));
	f_horizontalSpeed = DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("horizontalSpeed"));
	m_pigAttackRegion = NULL;
}

Player::~Player()
{
}

void Player::getAnimationNameByRole(std::string& name)
{
	if(m_currentRole == Monkey)
		name = MONKEY_TAG;
	else if(m_currentRole == Pig)
		name = PIG_TAG;
	else if(m_currentRole == Puffer)
		name = PUFFER_TAG;
}

void Player::changeAnotherRole()
{
	if (m_currentRole == Monkey)
	{
		changeRole(Pig);
	} 
	else if (m_currentRole == Pig)
	{
		changeRole(Monkey);
	}
}

STATUS Player::getAnimationNameByRoleAndStatus(std::string& name)
{
	getAnimationNameByRole(name);
	STATUS s = calculateStatuesForAnimation();

	if(s == NoAnyAction || s == Fly)
		name = name + "_" + NOANYACTION_TAG;
	else if(s == LeftWalk || s == RightWalk)
		name = name + "_" + WALK_TAG;
	else if(s == Jump)
		name = name + "_" + JUMP_TAG;
	else if (s == Die)
		name = name + "_" + DIE_TAG;
	else if (s == Attack)
		name = name + "_" + ATTACK_TAG;

	return s;
}

void Player::setRole(ROLE r)
{
	m_currentRole = r;
	updateArmatureAndPhyBodyByRoleAndStatus();
}
	
void Player::changeRole(ROLE r)
{
	if(m_currentRole != r)
	{
		setRole(r);
	}
}

Player::Player(ROLE r)
{
	setRole(r);
}

void Player::init()
{
	setRole(Monkey);
	m_currentStatus.clear();
	m_pigAttackRegion = NULL;
	setDir(NoMoveRight);
	updateArmatureAndPhyBodyByRoleAndStatus();
}

ROLE Player::getRole()
{
	return m_currentRole;
}

//STATUS Player::getStatus()
//{
//	return m_currentStatus;
//}

//void Player::setStatus(STATUS s)
//{
//	if (m_currentStatus == s)
//		return;
//
//	m_lastStatus = m_currentStatus;
//	m_currentStatus = s;
//
//	if (s == Jump)
//	{
//		setSpeed(getSpeed() + Vec2(0.0f, 100.0f));
//	}
//
//	if (m_currentStatus == NoAnyAction)
//		setSpeed(Vec2(0.0f, 0.0f));
//
//	updateArmatureAndPhyBodyByRoleAndStatus();
//	updateAnimatonPlayStatus();
//}

void Player::updateArmatureAndPhyBodyByRoleAndStatus()
{
	std::string name;
	STATUS s = getAnimationNameByRoleAndStatus(name);
	if(setArmatureWithAnimationName(name.c_str()))
	{
		updateBitMask();
		updateAnimatonPlayStatus(s);
	}
}

//void Player::setRoleAndStatus(ROLE r, STATUS s)
//{
//	m_currentRole = r;
//	m_currentStatus = s;
//	updateArmatureAndPhyBodyByRoleAndStatus();
//	updateAnimatonPlayStatus();
//}

void Player::changeStatus(STATUS s, bool isSet)
{
	std::vector<STATUS>::iterator it =  m_currentStatus.begin();
	bool isFind = false;
	bool isChanged = false;

	for(;it != m_currentStatus.end(); ++it)
	{
		if((*it) == s)
		{
			if(!isSet)//清除
			{
				m_currentStatus.erase(it);
				isFind = true;
				isChanged = true;
				break;
			}
			else
			{
				isFind = true;
				break;
			}
		}
	}

	if(isSet && !isFind)
	{
		int index = findStatus(Jump);

		if (index != -1 && s == Fly)//FLY替换JUMP
		{
			m_currentStatus[index] = Fly;
			isChanged = true;
		}
		else if (s == Jump && (findStatus(Fly) != -1 || findStatus(Attack) != -1))
		{
			//Jump不能替换Fly/Attack
		}
		else if (s != Fly)
		{
			m_currentStatus.push_back(s);
			isChanged = true;
		}
	}

	if (s == Fly && !isSet)
		isChanged = true;

	if(isChanged)
	{
		printStatus();
		updateDir(s, !isSet);
		updateArmatureAndPhyBodyByRoleAndStatus();
		updateSpeed(s, !isSet, isFind);
	}
}

void Player::updateAnimatonPlayStatus(STATUS s)
{
	if (s != Attack)
	{
		if (s == NoAnyAction || s == Fly)//除了站立和飞都需要动起来
		{
			m_armature->getAnimation()->playWithIndex(0);
			m_armature->getAnimation()->pause();
		}
		else if (s == LeftWalk || s == RightWalk)
		{
			m_armature->getAnimation()->playWithIndex(0);
		}
		else if (s == Jump || s == Die)
		{
			m_armature->getAnimation()->playWithIndex(0, -1, 0);  //播放完动画，就定格在最后一帧
		}


	}
	else
	{
		m_armature->getAnimation()->playWithIndex(0, -1, 0);
		m_armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Player::onAttackEnd,this));
	}
}

void Player::onCollisionHandle(Vec2 normal)
{
	if (normal.isZero())
		LOGD("All zero normal happens at Player.cpp 188");

	if (abs(normal.x) >= 0.5f)//有效值目前只看到1
	{
		setSpeed(Vec2(0.0f, getSpeed().y));

		if (normal.x > 0)//左边碰撞
		{
			//clearLikeFlyStatus();
		}
		else if (normal.x < 0)//右边碰撞
		{
			//clearLikeFlyStatus();
		}
	}
	else if (abs(normal.y) >= 0.5f)
	{
		setSpeed(Vec2(getSpeed().x, 0.0f));

		if (normal.y > 0)//下边碰撞
		{
			LOGD("remove Jump now\n");
			clearLikeFlyStatus();
			LOGD("remove Jump done\n");
		}
		else if (normal.y < 0)//上边碰撞
		{

		}
	}
	
	normal = Vec2(0.0f, 0.0f);
}

void Player::updateBitMask()
{
	m_phyBox->setCategoryBitmask(PLAYER_CATEGORYBITMASK);
	m_phyBox->setContactTestBitmask(PLATER_CONTACTTESTBITMASK);
	m_phyBox->setCollisionBitmask(PLAYER_COLLISIONBITMASK);
}

STATUS Player::calculateStatuesForAnimation()
{
	STATUS s;
	
	if(m_currentStatus.size() == 0)
		s = NoAnyAction;
	else
	{
		std::vector<STATUS>::const_iterator it = m_currentStatus.cbegin();	
		bool isDie = false;
		bool isJump = false;
		bool isWalk = false;
		bool isAttack = false;
		bool isFly = false;

		for(;it != m_currentStatus.cend(); ++it)
		{
			if((*it) == Die)
			{
				isDie = true;
			}
			else if((*it) == Jump)
			{
				isJump = true;
			}
			else if ((*it) == Fly)
			{
				isFly = true;
			}
			else if ((*it) == LeftWalk || (*it) == RightWalk)
			{
				isWalk = true;
			}
			else if ((*it) == Attack)
				isAttack = true;
		}

		if(isDie)
		{
			s = Die;
		}
		else if (isAttack)
		{
			s = Attack;
		}
		else if(isJump)
		{
			s = Jump;
		}
		else if (isFly)
		{
			s = Fly;
		}
		else if(isWalk)
		{
			s = LeftWalk;
		}

	}

	return s;
}

void Player::updateSpeed(STATUS s, bool isCancel, bool isFind)
{
	//Fly是更改的Jump态，不需要改变速度
	if((s == Jump) && !isCancel && !isFind)
	{
		setSpeed(getSpeed() + Vec2(0.0f, f_verticalSpeed));
	}
	else if((s == LeftWalk || s == RightWalk) && findStatus(Attack) == -1 )
	{
		if(m_dir == Left)
			setSpeed(Vec2(-1.0f*f_horizontalSpeed, getSpeed().y));
		else if(m_dir == Right)
			setSpeed(Vec2(f_horizontalSpeed, getSpeed().y));
		else if(m_dir == NoMoveLeft || m_dir == NoMoveRight)
			setSpeed(Vec2(0.0f, getSpeed().y));
	}
	else if (s == Attack )
	{
		if (!isCancel && !isFind && findStatus(Jump) == -1 && findStatus(Fly) == -1)
			setSpeed(Vec2(0.0f, getSpeed().y));
		else if (isCancel && isFind)
		{
			if (m_dir == Left)
				setSpeed(Vec2(-1.0f*f_horizontalSpeed, getSpeed().y));
			else if (m_dir == Right)
				setSpeed(Vec2(f_horizontalSpeed, getSpeed().y));
			else if (m_dir == NoMoveLeft || m_dir == NoMoveRight)
				setSpeed(Vec2(0.0f, getSpeed().y));
		}
	}
}

int Player::findStatus( STATUS s )
{
	if(m_currentStatus.size() == 0 && s == NoAnyAction)
		return 0;

	for(int i = 0; i < m_currentStatus.size(); ++i)
	{
		if(m_currentStatus[i] == s)
			return i;
	}

	return -1;
}

void Player::printStatus()
{
	std::string msg;

	if(m_currentStatus.size() == 0)
		msg = NOANYACTION_TAG;

	for(int i = 0; i < m_currentStatus.size(); ++i)
	{
		STATUS s = m_currentStatus[i];
		
		if(s == LeftWalk || s == RightWalk)
			msg= msg + WALK_TAG + ",";
		else if(s == Jump)
			msg= msg + JUMP_TAG + ",";
		else if (s == Die)
			msg = msg + DIE_TAG + ",";
		else if (s == Fly)
			msg = msg + "Fly" + ",";
		else if (s == Attack)
			msg = msg + ATTACK_TAG + ",";
	}

	msg+="\n";
	LOGD(msg.c_str(),NULL);
}

void Player::updateDir(STATUS s , bool isCancel)
{
	if(!isCancel)
	{
		if(s == LeftWalk)
			m_dir = Left;
		else if(s == RightWalk)
			m_dir = Right;
	}
	else
	{
		if(s == LeftWalk && findStatus(RightWalk) != -1)
			m_dir = Right;
		else if (s == RightWalk && findStatus(RightWalk) != -1)
			m_dir = Left;
		else if (s == LeftWalk && findStatus(RightWalk) == -1)
			m_dir = NoMoveLeft;
		else if(s == RightWalk && findStatus(LeftWalk) == -1)
			m_dir = NoMoveRight;
	}
	
}

void Player::onAttackEnd(cocostudio::Armature * armatrue, cocostudio::MovementEventType type, const std::string& id)
{
	changeStatus(Attack, false);
	changeStatus(Fly, true);

	//如果当前角色是pig，攻击动画播放完成后，生成近身攻击区域
	if (Pig == getRole())
	{
		creatPigAttackRegion(armatrue);
	} 
}

void Player::removePigAttackRegion(float delay)
{
	m_phyBox->removeShape(m_pigAttackRegion);
}

void Player::creatPigAttackRegion(cocostudio::Armature * armatrue)
{
	int direction_flag;
	cocos2d::Size attackRegionSize = armatrue->getContentSize();
	attackRegionSize.width = attackRegionSize.width / 3.0f;
	float attackRegionOffset = attackRegionSize.width * 2.0f;
	if (Left == getDir() || NoMoveLeft == getDir())
	{
		direction_flag = -1;
	}
	else
	{
		direction_flag = 1;
	}
	//如果当前角色是pig，攻击动画播放完成后，生成近身攻击区域
	m_pigAttackRegion = cocos2d::PhysicsShapeBox::create(attackRegionSize, MY_PHYSICSBODY_MATERIAL_DEFAULT, Vec2(attackRegionOffset * direction_flag, 0.0f));
	m_phyBox->addShape(m_pigAttackRegion);
	//延迟一秒后攻击区域消失
	Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(Player::removePigAttackRegion, this), this, 0, 0, 1, false, "delayRemoveAttackRegion");
}

void Player::clearLikeFlyStatus()
{
	//消除jump会消除速度所以不能简单的消除
	int index = findStatus(Fly);

	if (index == -1)//找不到Fly说明是普通的跳跃
	{
		changeStatus(Jump, false);
	}
	else
	{
		changeStatus(Fly, false);
	}	
}
