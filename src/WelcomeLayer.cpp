#include "WelcomeLayer.h"
#include "ResourceMgr.h"
#include "ResourceLoader.h"
#include "GameScene.h"

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

	sprite->setPosition(Vec2(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height*0.618 ));
	

	cocostudio::Armature * armature = cocostudio::Armature::create("monkey_jump");
	armature->getAnimation()->playWithIndex(0);
	//armature->setPosition(Vec2(origin.x + visibleSize.width / 2 - sprite->getContentSize().width / 2,
	//	origin.y + visibleSize.height*0.4 - sprite->getContentSize().height / 2));
	sprite->addChild(armature);
	addChild(sprite);

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(WelcomeLayer::onTouchesBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void WelcomeLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}
