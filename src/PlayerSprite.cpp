#include "PlayerSprite.h"

USING_NS_CC;

PlayerSprite::PlayerSprite()
{
	m_player = NULL;
	this->setTag(PLAYER_TAG);
}


PlayerSprite::~PlayerSprite()
{
	delete m_player;
}

bool PlayerSprite::init()
{
	if (!Sprite::init())
		return false;
	
	m_player = new Player();
	m_player->init();
	cocostudio::Armature* armature = m_player->getArmature();
	addChild(armature);
	m_player->bindPhyBody(this);

	return true;
}

void PlayerSprite::jump(bool isCancel)
{
	//只能设置跳跃不能通过按键取消
	if (!isCancel)
		m_player->changeStatus(STATUS::Jump, true);
}

void PlayerSprite::onCollisionHandle(float dt)
{
	m_player->onCollisionHandle(m_normal);
	Director::getInstance()->getScheduler()->unschedule(schedule_selector(PlayerSprite::onCollisionHandle), this);
}

void PlayerSprite::setNormal(Vec2 normal)
{
	m_normal = normal;
}

void PlayerSprite::leftWalk( bool isCancel )
{
	m_player->changeStatus(STATUS::LeftWalk, !isCancel);
	updateDirection();
}

void PlayerSprite::rightWalk( bool isCancel )
{
	m_player->changeStatus(STATUS::RightWalk, !isCancel);
	updateDirection();
}

void PlayerSprite::updateDirection()
{
	if(m_player->getDir() == Right)
		setScaleX(1);
	else if(m_player->getDir() == Left)
		setScaleX(-1);
}

void PlayerSprite::attack( bool isCancel )
{
	if (!isCancel)
		m_player->changeStatus(STATUS::Attack, true);
}

void PlayerSprite::changeRole( ROLE role )
{
	m_player->changeRole(role);
}





