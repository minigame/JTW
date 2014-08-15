#include "WelcomeLayer.h"
#include "ResourceMgr.h"
#include "ResourceLoader.h"

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

	cocostudio::Armature * armature = cocostudio::Armature::create("NewAnimation1");
	armature->getAnimation()->playWithIndex(0);
	armature->setPosition(Vec2(origin.x + visibleSize.width / 2 - sprite->getContentSize().width / 2,
		origin.y + visibleSize.height*0.4 - sprite->getContentSize().height / 2));
	sprite->addChild(armature);
	addChild(sprite);

	return true;
}
