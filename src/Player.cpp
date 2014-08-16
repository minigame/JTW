#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}


void Player::getAnimationNameByRole(std::string& name)
{
	if(m_currentRole == Monkey)
		name = "monkey";
	else if(m_currentRole == Pig)
		name = "pig";
	else if(m_currentRole == Puffer)
		name = "puffer";
}


void Player::getAnimationNameByRoleAndStatus(std::string& name)
{
	getAnimationNameByRole(name);
	/*char roleName[10] = {0};
	sprintf(roleName, "%s_", getAnimationNameByRole());*/
	
	//char statusName[15] = {0};
	if(m_currentStatus == NoAnyAction)
		name =name + "_walk";
	else if(m_currentStatus == Walk)
		name =name + "_walk";
	else if(m_currentStatus == Jump)
		name =name + "_jump";
	else if(m_currentStatus == Die)
		name =name + "_die";
}



void Player::setRole(ROLE r)
{
	
	m_currentRole = r;
	std::string name;
	getAnimationNameByRoleAndStatus(name);
	setArmatureWithAnimationName(name.c_str());
	setPhyByArmatureContentSize();
	
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
	}
}

