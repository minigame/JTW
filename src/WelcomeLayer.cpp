#include "WelcomeLayer.h"
#include "ResourceMgr.h"

USING_NS_CC;

WelcomeLayer::WelcomeLayer()
{
}


WelcomeLayer::~WelcomeLayer()
{
}

bool WelcomeLayer::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *sprite = Sprite::createWithSpriteFrame(ResourceMgr::getInstance()->getImage("GameTitle"));
	sprite->setPosition(Vec2(origin.x + visibleSize.width/2 - sprite->getContentSize().width/2,
		origin.y + visibleSize.height*0.4 - sprite->getContentSize().height/2));

	addChild(sprite);

	return true;
}
