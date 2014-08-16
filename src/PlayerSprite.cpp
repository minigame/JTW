#include "PlayerSprite.h"

USING_NS_CC;

PlayerSprite::PlayerSprite()
{
	m_walkAnimation = NULL;
	m_isWalk = true;
}


PlayerSprite::~PlayerSprite()
{
}

bool PlayerSprite::init()
{
	if (!Sprite::init())
		return false;
	

	m_walkAnimation = cocostudio::Armature::create("NewAnimation1");
	m_walkAnimation->getAnimation()->playWithIndex(0);
	//armature->setPosition(Vec2(origin.x + visibleSize.width / 2 - sprite->getContentSize().width / 2,
	//	origin.y + visibleSize.height*0.4 - sprite->getContentSize().height / 2));
	addChild(m_walkAnimation);

	return true;
}

void PlayerSprite::walk()
{
	m_isWalk = true;
	m_walkAnimation->getAnimation()->resume();
}

void PlayerSprite::stop()
{
	m_isWalk = false;
	m_walkAnimation->getAnimation()->pause();
}

bool PlayerSprite::getState() const
{
	return m_isWalk;
}


