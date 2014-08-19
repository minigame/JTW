#include "Player.h"


Player::Player()
{
	m_currentRole = ROLE::Monkey;
	setDir(Right);
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


STATUS Player::getAnimationNameByRoleAndStatus(std::string& name)
{
	getAnimationNameByRole(name);
	STATUS s = calculateStatuesForAnimation();

	if(s == NoAnyAction)
		name = name + "_" + NOANYACTION_TAG;
	else if(s == LeftWalk || s == RightWalk)
		name = name + "_" + WALK_TAG;
	else if(s == Jump)
		name = name + "_" + JUMP_TAG;
	else if (s == Die)
		name = name + "_" + DIE_TAG;

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
	setDir(Right);
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
		m_currentStatus.push_back(s);
		isChanged = true;
	}

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
	if (s == NoAnyAction)//除了站立都需要动起来
	{
		m_armature->getAnimation()->playWithIndex(0);
		m_armature->getAnimation()->pause();
	}
	else if(s == LeftWalk || s == RightWalk)
	{
		m_armature->getAnimation()->playWithIndex(0);
	}
	else if(s == Jump || s == Die)
	{
		m_armature->getAnimation()->playWithIndex(0, -1, 0);  //播放完动画，就定格在最后一帧
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

		}
		else if (normal.x < 0)//右边碰撞
		{

		}
	}
	else if (abs(normal.y) >= 0.5f)
	{
		setSpeed(Vec2(getSpeed().x, 0.0f));

		if (normal.y > 0)//下边碰撞
		{
			changeStatus(Jump, false);
			LOGD("remove Jump");
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
			else if((*it) == LeftWalk || (*it) == RightWalk)
			{
				isWalk = true;
			}
		}

		if(isDie)
		{
			s = Die;
		}
		else if(isJump)
		{
			s = Jump;
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
	if(s == Jump && !isCancel && !isFind)
	{
		setSpeed(getSpeed() + Vec2(0.0f, 200.0f));
	}
	else if(s == LeftWalk || s == RightWalk)
	{
		if(m_dir == Left)
			setSpeed(Vec2(-200.0f, getSpeed().y));
		else if(m_dir == Right)
			setSpeed(Vec2(200.0f, getSpeed().y));
		else if(m_dir == NoMoveLeft || m_dir == NoMoveRight)
			setSpeed(Vec2(0.0f, getSpeed().y));
	}
}

bool Player::findStatus( STATUS s )
{
	if(m_currentStatus.size() == 0 && s == NoAnyAction)
		return true;

	std::vector<STATUS>::const_iterator it = m_currentStatus.cbegin();

	for(; it != m_currentStatus.cend(); ++it)
	{
		if((*it) == s)
			return true;
	}

	return false;
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
		else if(s == Die)
			msg= msg + DIE_TAG + ",";
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
		if(s == LeftWalk && findStatus(RightWalk))
			m_dir = Right;
		else if(s == RightWalk && findStatus(LeftWalk))
			m_dir = Left;
		else if(s == LeftWalk && !findStatus(RightWalk))
			m_dir = NoMoveLeft;
		else if(s == RightWalk && !findStatus(LeftWalk))
			m_dir = NoMoveRight;
	}
	
}

