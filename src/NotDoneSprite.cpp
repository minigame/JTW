#include "NotDoneSprite.h"
#include "ResourceMgr.h"

USING_NS_CC;

NotDoneSprite::NotDoneSprite()
{
	m_listener = NULL;
	m_isRemove = false;
}


NotDoneSprite::~NotDoneSprite()
{
}

bool NotDoneSprite::init()
{
	if (!Sprite::init())
		return false;

	if (!initWithTexture(ResourceMgr::getInstance()->getImage("HaveNotDone")))
		return false;

	//topest!
	this->setLocalZOrder(NOT_HAVE_DONE_SPRITE_ZORDER);
	this->setPosition(this->getContentSize() / 2);

	return true;
}

void NotDoneSprite::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
	if (!m_isRemove)
	{
		m_isRemove = true;
		this->removeFromParent();
	}
}

void NotDoneSprite::onEnter()
{
	Sprite::onEnter();

	m_listener = EventListenerTouchAllAtOnce::create();
	m_listener->onTouchesBegan = CC_CALLBACK_2(NotDoneSprite::onTouchesBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
}

void NotDoneSprite::onExit()
{
	Sprite::onExit();

	Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
}
