#include "WelcomeLayer.h"
#include "GameScene.h"
#include "MissionScene.h"

USING_NS_CC;

WelcomeLayer::WelcomeLayer()
{
	m_isLoad = false;
	m_actionObj = NULL;
	m_hideWidget = NULL;
}


WelcomeLayer::~WelcomeLayer()
{
}

bool WelcomeLayer::init()
{
	if (!Layer::init())
		return false;

	cocostudio::ActionManagerEx::destroyInstance();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite * background = Sprite::createWithTexture(ResourceMgr::getInstance()->getImage("StartBackground"));
	background->setPosition(visibleSize.width - background->getContentSize().width/2, background->getContentSize().height/2);
	float delta = background->getContentSize().width - visibleSize.width;
	auto moveLeftAction = MoveBy::create(6, Vec2(delta, 0));
	auto moveRightAction = MoveBy::create(6, Vec2(-delta, 0));
	auto sequence = Sequence::create(moveLeftAction, moveRightAction, NULL);
	auto repeat = RepeatForever::create(sequence);
	background->runAction(repeat);
	addChild(background, 1);

	ui::Widget* widget = ResourceLoader::getInstance()->loadUIFromFile("StartMenu/StartMenu.ExportJson");
	addChild(widget, 2);

	m_hideWidget = ResourceLoader::getInstance()->loadUIFromFile("YourSisiter/YourSisiter.ExportJson");
	addChild(m_hideWidget, 0);

	ui::Button * btnCancel = (ui::Button*)widget->getChildByName("Button_Cancel");
	ui::Button * btnStart = (ui::Button*)widget->getChildByName("Button_Start");

	ui::Button* btnConfirm = (ui::Button*)m_hideWidget->getChildByName("Button_Confirm");

	btnCancel->addTouchEventListener(CC_CALLBACK_2(WelcomeLayer::onCancelTouch, this));
	btnStart->addTouchEventListener(CC_CALLBACK_2(WelcomeLayer::onStartTouch, this));
	btnConfirm->addTouchEventListener(CC_CALLBACK_2(WelcomeLayer::onConfirm, this));

	return true;
}

void WelcomeLayer::onCancelTouch( cocos2d::Ref * obj, ui::Widget::TouchEventType type )
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
	}
	else if(type == ui::Widget::TouchEventType::ENDED)
	{
		m_hideWidget->setLocalZOrder(100);
		m_actionObj->stop();
		m_actionObj = cocostudio::ActionManagerEx::getInstance()->playActionByName("YourSisiter.ExportJson", "YourSisiter");
	}
}

void WelcomeLayer::onStartTouch( cocos2d::Ref * obj, ui::Widget::TouchEventType type )
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
	}
	else if(type == ui::Widget::TouchEventType::ENDED && !m_isLoad)
	{
		m_isLoad = true;

		//必须在Create之前
		m_actionObj->stop();
		cocostudio::ActionManagerEx::destroyInstance();

		auto scene = MissionScene::create();
		TransitionScene *transition = TransitionFade::create(1, scene);
		Director::getInstance()->replaceScene(transition);
	}
}

void WelcomeLayer::onEnter()
{
	Layer::onEnter();

	//这里的json不能是全相对路径，只能是文件名
	m_actionObj = cocostudio::ActionManagerEx::getInstance()->playActionByName("StartMenu.ExportJson", "Start");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACK_TITLE, true);
}

void WelcomeLayer::onExit()
{
	Layer::onExit();
}

void WelcomeLayer::onConfirm(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
	}
	else if (type == ui::Widget::TouchEventType::ENDED && !m_isLoad)
	{
		m_isLoad = true;

		//必须在Create之前
		m_actionObj->stop();
		cocostudio::ActionManagerEx::destroyInstance();

		auto scene = MissionScene::create();
		TransitionScene *transition = TransitionFade::create(1, scene);
		Director::getInstance()->replaceScene(transition);
	}
}
