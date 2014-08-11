#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}


void Player::setRole(ROLE r)
{
	m_eCurrentRole = r;
}
	
void Player::changeRole(ROLE r)
{
	if(m_eCurrentRole != r)
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
