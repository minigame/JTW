#include "MissionScene.h"
#include "WelcomeScene.h"
#include "GameScene.h"
#include "NotDoneSprite.h"
#include "DiCiData.h"



USING_NS_CC;

extern std::vector<DiCiData*>* diciVector;

MissionScene::MissionScene()
{
	m_isLoad = false;
	m_mission_num = 0;
	m_pig1 = NULL;
	m_pig2 = NULL;
	m_actionObj = NULL;
	m_btnCancel = NULL;
	m_btnStart = NULL;
	m_btnM1 = NULL;
	m_btnM2 = NULL;
	m_btnM3 = NULL;
}


MissionScene::~MissionScene()
{
}

bool MissionScene::init()
{
	if (!Scene::init())
		return false;

	ui::Widget* widget = ResourceLoader::getInstance()->loadUIFromFile("SelectMission/SelectMission.ExportJson");
	addChild(widget, 0);

	m_btnCancel = (ui::Button*)widget->getChildByName("Button_Cancel");
	m_btnStart = (ui::Button*)widget->getChildByName("Button_Start");
	m_btnM1 = (ui::Button*)widget->getChildByName("Button_Mission_1");
	m_btnM2 = (ui::Button*)widget->getChildByName("Button_Mission_2");
	m_btnM3 = (ui::Button*)widget->getChildByName("Button_Mission_3");
	ui::ImageView *pig1 = (ui::ImageView*)widget->getChildByName("Pig_1");
	ui::ImageView *pig2 = (ui::ImageView*)widget->getChildByName("Pig_2");

	m_pig1 = Armature::create("pig_run");
	m_pig2 = Armature::create("pig_fight");

	m_pig1->setPosition(pig1->getPosition());
	m_pig2->setPosition(pig2->getPosition());

	m_pig1->setOpacity(0);
	m_pig2->setOpacity(0);

	addChild(m_pig1, 1);
	addChild(m_pig2, 2);

	m_pig1->getAnimation()->playWithIndex(0);
	m_mission_num = 1;

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
		m_actionObj->stop();
		cocostudio::ActionManagerEx::destroyInstance();
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

		if (m_mission_num == 3)
		{
			NotDoneSprite * notObjc = NotDoneSprite::create();
			addChild(notObjc, notObjc->getLocalZOrder());
		}
		else
		{
			m_isLoad = true;
			m_actionObj->stop();
			cocostudio::ActionManagerEx::destroyInstance();

			if(diciVector->size())
			{
				for(int i = 0;i<diciVector->size();i++)
					delete (*diciVector)[i];
				diciVector->clear();
			}

			//auto scene = GameScene::create();
			GameScene* scene = new GameScene(m_mission_num);
			scene->init();
			TransitionScene *transition = TransitionFade::create(1, scene);
			Director::getInstance()->replaceScene(transition);
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
	}
}

void MissionScene::onM1Touch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
		m_mission_num = 1;
		m_pig1->setOpacity(255);
		m_pig1->getAnimation()->playWithIndex(0);
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
		m_pig2->getAnimation()->playWithIndex(0);
		m_pig1->setOpacity(0);
	}

}

void MissionScene::onM3Touch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
		m_mission_num = 3;
		m_pig2->setOpacity(0);
		m_pig1->setOpacity(0);
	}

}

void MissionScene::onEnter()
{
	Scene::onEnter();

	CallFunc * callFunc = CallFunc::create(CC_CALLBACK_0(MissionScene::isAnimationPlayed, this));
	m_actionObj = cocostudio::ActionManagerEx::getInstance()->playActionByName("SelectMission.ExportJson", "SelectMission", callFunc);

	if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACK_TITLE);
}

void MissionScene::onExit()
{
	Scene::onExit();
}

void MissionScene::isAnimationPlayed()
{
	m_btnCancel->addTouchEventListener(CC_CALLBACK_2(MissionScene::onCancelTouch, this));
	m_btnStart->addTouchEventListener(CC_CALLBACK_2(MissionScene::onStartTouch, this));
	m_btnM1->addTouchEventListener(CC_CALLBACK_2(MissionScene::onM1Touch, this));
	m_btnM2->addTouchEventListener(CC_CALLBACK_2(MissionScene::onM2Touch, this));
	m_btnM3->addTouchEventListener(CC_CALLBACK_2(MissionScene::onM3Touch, this));
	m_pig1->setOpacity(255);
}
