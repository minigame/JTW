#include "PlayerSprite.h"

USING_NS_CC;

PlayerSprite::PlayerSprite()
{
	m_player = NULL;
	this->setTag(PLAYER_TAG);
}


PlayerSprite::~PlayerSprite()
{
}

bool PlayerSprite::init()
{
	if (!Sprite::init())
		return false;
	
	m_player = new Player();
	m_player->init();
	cocostudio::Armature* armature = m_player->getArmature();
	//armature->setPosition(Vec2(origin.x + visibleSize.width / 2 - sprite->getContentSize().width / 2,
	//	origin.y + visibleSize.height*0.4 - sprite->getContentSize().height / 2));
	addChild(armature);
	m_player->bindPhyBody(this);

	return true;
}

void PlayerSprite::walk(bool forward)
{
	m_player->changeStatus(STATUS::Walk);

	if (forward)
	{
		m_player->setSpeed(Vec2(100.0f, 0.0f));
	}
	else
	{
		m_player->setSpeed(Vec2(-100.0f, 0.0f));
	}
}

void PlayerSprite::noAction()
{
	m_player->changeStatus(STATUS::NoAnyAction);
}

void PlayerSprite::jump()
{
	m_player->changeStatus(STATUS::Jump);
}

Player* PlayerSprite::getPlayer()
{
	return m_player;
}

void PlayerSprite::onCollisionHandle(float dt)
{
	m_player->onCollisionHandle();
}





