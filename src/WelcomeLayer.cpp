#include "WelcomeLayer.h"
#include "GameScene.h"
#include "MissionScene.h"

USING_NS_CC;

WelcomeLayer::WelcomeLayer()
{
	m_isLoad = false;
	m_actionObj = NULL;
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

	Sprite * background = Sprite::createWithTexture(ResourceMgr::getInstance()->getImage("StartBackground"));
	background->setPosition(visibleSize.width - background->getContentSize().width/2, background->getContentSize().height/2);
	float delta = background->getContentSize().width - visibleSize.width;
	auto moveLeftAction = MoveBy::create(6, Vec2(delta, 0));
	auto moveRightAction = MoveBy::create(6, Vec2(-delta, 0));
	auto sequence = Sequence::create(moveLeftAction, moveRightAction, NULL);
	auto repeat = RepeatForever::create(sequence);
	background->runAction(repeat);
	addChild(background);

	ui::Widget* widget = ResourceLoader::getInstance()->loadUIFromFile("StartMenu/StartMenu.ExportJson");
	addChild(widget);

	ui::Button * btnCancel = (ui::Button*)widget->getChildByName("Button_Cancel");
	ui::Button * btnStart = (ui::Button*)widget->getChildByName("Button_Start");

	btnCancel->addTouchEventListener(CC_CALLBACK_2(WelcomeLayer::onCancelTouch, this));
	btnStart->addTouchEventListener(CC_CALLBACK_2(WelcomeLayer::onStartTouch, this));

	return true;
}

void WelcomeLayer::onCancelTouch( cocos2d::Ref * obj, ui::Widget::TouchEventType type )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	cocostudio::ActionManagerEx::getInstance()->playActionByName("StartMenu.ExportJson", "Start");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
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
		auto scene = MissionScene::create();
		//TransitionScene *transition = TransitionFade::create(1, scene);
		Director::getInstance()->replaceScene(scene);
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

	m_actionObj->stop();
}
