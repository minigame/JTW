#include "PlayerSprite.h"

USING_NS_CC;

PlayerSprite::PlayerSprite()
{
	m_player = NULL;
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

	return true;
}

void PlayerSprite::walk()
{
	m_player->changeStatus(STATUS::Walk);
}

void PlayerSprite::jump()
{
	m_player->changeStatus(STATUS::Jump);
}

Player* PlayerSprite::getPlayer()
{
	return m_player;
}




