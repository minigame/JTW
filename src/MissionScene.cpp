#include "MissionScene.h"
#include "WelcomeScene.h"
#include "GameScene.h"

USING_NS_CC;

MissionScene::MissionScene()
{
	m_isLoad = false;
	m_mission_num = 0;
	m_pig1 = NULL;
	m_pig2 = NULL;
	m_actionObj = NULL;
}


MissionScene::~MissionScene()
{
}

bool MissionScene::init()
{
	if (!Scene::init())
		return false;

	ui::Widget* widget = ResourceLoader::getInstance()->loadUIFromFile("SelectMission/SelectMission.ExportJson");
	addChild(widget);

	ui::Button * btnCancel = (ui::Button*)widget->getChildByName("Button_Cancel");
	ui::Button * btnStart = (ui::Button*)widget->getChildByName("Button_Start");
	ui::Button * btnM1 = (ui::Button*)widget->getChildByName("Button_Mission_1");
	ui::Button * btnM2 = (ui::Button*)widget->getChildByName("Button_Mission_2");
	ui::Button * btnM3 = (ui::Button*)widget->getChildByName("Button_Mission_3");
	m_pig1 = (ui::ImageView*)widget->getChildByName("Pig_1");
	m_pig2 = (ui::ImageView*)widget->getChildByName("Pig_2");

	btnCancel->addTouchEventListener(CC_CALLBACK_2(MissionScene::onCancelTouch, this));
	btnStart->addTouchEventListener(CC_CALLBACK_2(MissionScene::onStartTouch, this));
	btnM1->addTouchEventListener(CC_CALLBACK_2(MissionScene::onM1Touch, this));
	btnM2->addTouchEventListener(CC_CALLBACK_2(MissionScene::onM2Touch, this));
	btnM3->addTouchEventListener(CC_CALLBACK_2(MissionScene::onM3Touch, this));

	return true;
}

void MissionScene::onCancelTouch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
	}
	else if (type == ui::Widget::TouchEventType::ENDED && !m_isLoad)
	{
		m_isLoad = true;
		auto scene = WelcomeScene::create();
		TransitionScene *transition = TransitionFade::create(1, scene);
		Director::getInstance()->replaceScene(transition);
	}
	
}

void MissionScene::onStartTouch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
	}
	else if (type == ui::Widget::TouchEventType::ENDED && !m_isLoad)
	{
		m_isLoad = true;
		auto scene = GameScene::create();
		TransitionScene *transition = TransitionFade::create(1, scene);
		Director::getInstance()->replaceScene(transition);
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
}

void MissionScene::onM1Touch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
		m_mission_num = 1;
		m_pig1->setOpacity(255);
		m_pig2->setOpacity(0);
	}

}

void MissionScene::onM2Touch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
		m_mission_num = 2;
		m_pig2->setOpacity(255);
		m_pig1->setOpacity(0);
	}

}

void MissionScene::onM3Touch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
		m_mission_num = 1;
		m_pig2->setOpacity(0);
		m_pig1->setOpacity(0);
	}

}

void MissionScene::onEnter()
{
	Scene::onEnter();

	m_actionObj = cocostudio::ActionManagerEx::getInstance()->playActionByName("SelectMission.ExportJson", "SelectMission");
}
