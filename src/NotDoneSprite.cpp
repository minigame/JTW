#include "NotDoneSprite.h"
#include "ResourceMgr.h"

USING_NS_CC;

NotDoneSprite::NotDoneSprite()
{
	m_isRemove = false;
	m_listener = NULL;
	m_ui = NULL;
}


NotDoneSprite::~NotDoneSprite()
{
}

bool NotDoneSprite::initWithNode(cocos2d::Node* node)
{
	if (!Sprite::init())
		return false;

	if (!initWithTexture(ResourceMgr::getInstance()->getImage("HaveNotDone")))
		return false;

	//topest!
	setLocalZOrder(NOT_HAVE_DONE_SPRITE_ZORDER);
	setPosition(this->getContentSize() / 2);

	IUIHaveNotDoneSprite * ui = dynamic_cast<IUIHaveNotDoneSprite*>(node);

	if (ui != NULL)
	{
		m_ui = ui;
		ui->setUIWidgetsEnable(false);
	}

	node->addChild(this, NOT_HAVE_DONE_SPRITE_ZORDER);

	return true;
}

bool NotDoneSprite::onToucheBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (!m_isRemove)
	{
		m_isRemove = true;

		if (m_ui)
			m_ui->setUIWidgetsEnable(true);

		this->removeFromParent();
	}

	return true;
}

void NotDoneSprite::onEnter()
{
	Sprite::onEnter();

	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(false);
	m_listener->onTouchBegan = CC_CALLBACK_2(NotDoneSprite::onToucheBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
}

void NotDoneSprite::onExit()
{
	Sprite::onExit();

	Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
}

NotDoneSprite* NotDoneSprite::create(cocos2d::Node* node)
{
	NotDoneSprite *pRet = new NotDoneSprite();
	if (pRet && pRet->initWithNode(node))
	{
		pRet->autorelease();
		return pRet;
	}
		else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
