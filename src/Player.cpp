#include "Player.h"


Player::Player()
{
	m_currentStatus = NoAnyAction;
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


void Player::getAnimationNameByRoleAndStatus(std::string& name)
{
	getAnimationNameByRole(name);
	/*char roleName[10] = {0};
	sprintf(roleName, "%s_", getAnimationNameByRole());*/
	
	//char statusName[15] = {0};
	if(m_currentStatus == NoAnyAction)
		name =name + "_" + WALK_TAG;
	else if(m_currentStatus == Walk)
		name = name + "_" + WALK_TAG;
	else if(m_currentStatus == Jump)
		name = name + "_" + JUMP_TAG;
	else if(m_currentStatus == Die)
		name = name + "_" + DIE_TAG;
}



void Player::setRole(ROLE r)
{
	m_currentRole = r;
	setStatus(m_currentStatus);
}
	
void Player::changeRole(ROLE r)
{
	if(m_currentRole != r)
	{
		setRole(r);
		updateAnimatonPlayStatus();
	}
}


Player::Player(ROLE r)
{
	m_currentStatus = NoAnyAction;
	setRole(r);
}



void Player::init()
{
	setRole(ROLE::Monkey);
}

ROLE Player::getRole()
{
	return m_currentRole;
}


STATUS Player::getStatus()
{
	return m_currentStatus;
}


void Player::setStatus(STATUS s)
{
	m_currentStatus = s;
	std::string name;
	getAnimationNameByRoleAndStatus(name);
	setArmatureWithAnimationName(name.c_str());
	setPhyByArmatureContentSize();
}


void Player::changeStatus(STATUS s)
{
	if(m_currentStatus != s)
	{
		setStatus(s);
		updateAnimatonPlayStatus();
	}
}

void Player::updateAnimatonPlayStatus()
{
	if (m_currentStatus != NoAnyAction)//除了站立都需要动起来
	{
		m_armature->getAnimation()->playWithIndex(0);
	}
}

