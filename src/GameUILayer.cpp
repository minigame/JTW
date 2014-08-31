#include "GameUILayer.h"
#include "CallBackMgr.h"
#include "MissionScene.h"
#include "GameScene.h"
#include "DiCiData.h"
#include "NotDoneSprite.h"
#include "ResourceMgr.h"
USING_NS_CC;

extern std::vector<DiCiData*>* diciVector;

GameUILayer::GameUILayer()
{
    LOGD("GameUILayer created");
	m_icon_pig = NULL;
	m_icon_monkey = NULL;
	m_actionObj = NULL;
    m_musicEnable = 1;
    m_previousVolume = 0.0;
	m_playUI = NULL;
	m_lostUI = NULL;
	m_succUI = NULL;
	m_missionNum = 0;
	m_isSucc = false;
	m_isEnter = false;
}

GameUILayer::~GameUILayer()
{
    LOGD("GameUILayer destory");
	CallBackMgr::getInstance()->unRegisterFunction(PLAYER_ROLE_CHANGED, this);
	CallBackMgr::getInstance()->unRegisterFunction(PlAYER_DEAD, this);
	CallBackMgr::getInstance()->unRegisterFunction(NEXT_MISSION, this);
}

bool GameUILayer::init()
{
	if (Layer::init())
	{
		cocostudio::ActionManagerEx::destroyInstance();
        m_playUI = ResourceLoader::getInstance()->loadUIFromFile("UI/UI1_1.ExportJson");
		m_playUI->setTouchEnabled(false);
		addChild(m_playUI);
		m_playUI->setTag(WIDGETUI_TAG);

		ui::Button * btnA = (ui::Button*)m_playUI->getChildByName("Button_A");
		ui::Button * btnB = (ui::Button*)m_playUI->getChildByName("Button_B");
		ui::Button * btnleft = (ui::Button*)m_playUI->getChildByName("Button_Left");
		ui::Button * btnright = (ui::Button*)m_playUI->getChildByName("Button_Right");
		ui::Button * btnPause = (ui::Button*)m_playUI->getChildByName("Button_Pause");
        
		m_icon_pig = (ui::ImageView*)m_playUI->getChildByName("Icon_Pig");
		m_icon_monkey = (ui::ImageView*)m_playUI->getChildByName("Icon_Monkey");
		ui::ImageView * HP_1 = (ui::ImageView*)m_playUI->getChildByName("HP_1");
		ui::ImageView * HP_2 = (ui::ImageView*)m_playUI->getChildByName("HP_2");
		ui::ImageView * HP_3 = (ui::ImageView*)m_playUI->getChildByName("HP_3");

		m_firstPos = m_icon_monkey->getPosition();
		m_secondPos = m_icon_pig->getPosition();

		btnA->setOpacity(128);
		btnB->setOpacity(128);
		btnleft->setOpacity(128);
		btnright->setOpacity(128);

		btnA->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onATouch, this));
		btnB->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onBTouch, this));
		btnleft->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onLeftTouch, this));
		btnright->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onRightTouch, this));
		btnPause->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onPauseTouch, this));

		m_icon_pig->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onChangePig, this));
		m_icon_monkey->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onChangeMonkey, this));

		CallBackMgr::getInstance()->registerFunction(PLAYER_ROLE_CHANGED, this, MY_CALL_BACK_1(GameUILayer::onChangedRole, this));
		CallBackMgr::getInstance()->registerFunction(PlAYER_DEAD, this, MY_CALL_BACK_1(GameUILayer::onPlayerDead, this));
		CallBackMgr::getInstance()->registerFunction(NEXT_MISSION, this, MY_CALL_BACK_1(GameUILayer::onNextMission, this));

#if defined(WIN32) or defined(__OSX__)
        // Add keyboard event support
		auto keyboardListener = EventListenerKeyboard::create();
		keyboardListener->onKeyPressed = CC_CALLBACK_2(GameUILayer::keyPressed, this);
		keyboardListener->onKeyReleased = CC_CALLBACK_2(GameUILayer::keyReleased, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
#endif
   
		return true;
	} else {
		return false;
	}
}

#if defined(WIN32) or defined(__OSX__)
void GameUILayer::keyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
    LOGD("key is pressed");
    if (keyCode == EventKeyboard::KeyCode::KEY_A) 
	{
        this->delegator->onLeftButton(false);
    } 
	else if (keyCode == EventKeyboard::KeyCode::KEY_D ) 
	{
        this->delegator->onRightButton(false);
    } 
	else if (keyCode == EventKeyboard::KeyCode::KEY_J ) 
	{
        this->delegator->onActionButton(false);
    } 
	else if (keyCode == EventKeyboard::KeyCode::KEY_K) 
	{
        this->delegator->onJumpButton(false);
    }
	else if (keyCode == EventKeyboard::KeyCode::KEY_U)
	{
		 this->delegator->onChangeRole(Monkey);
		 CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_CHANGE_CHARACTER);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_I)
	{
		this->delegator->onChangeRole(Pig);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_CHANGE_CHARACTER);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_O)
    {
        // toggle background music and effect
        if (m_musicEnable) {
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
            m_previousVolume = CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume();
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0);
            m_musicEnable = 0;
            LOGD("stop the music");
        }
        else {
            CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(m_previousVolume);
            m_musicEnable = 1;
            LOGD("enable the music");
        }
    }
}

void GameUILayer::keyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    LOGD("key is released");
    if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        this->delegator->onLeftButton(true);
    } else if (keyCode == EventKeyboard::KeyCode::KEY_D ) {
        this->delegator->onRightButton(true);
    } else if (keyCode == EventKeyboard::KeyCode::KEY_J ) {
        this->delegator->onActionButton(true);
    } else if (keyCode == EventKeyboard::KeyCode::KEY_K) {
        this->delegator->onJumpButton(true);
    }
}
#endif

void GameUILayer::onATouch(Ref * obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
	{
		this->delegator->onActionButton(true);
	}
	else if (type == ui::Widget::TouchEventType::BEGAN)
	{
		this->delegator->onActionButton(false);
	}
	
}

void GameUILayer::onBTouch(Ref * obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
	{
		this->delegator->onJumpButton(true);
	}
	else if (type == ui::Widget::TouchEventType::BEGAN)
	{
		this->delegator->onJumpButton(false);
	}
}

void GameUILayer::onLeftTouch(Ref * obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
	{
		this->delegator->onLeftButton(true);
	}
	else if (type == ui::Widget::TouchEventType::BEGAN)
	{
		this->delegator->onLeftButton(false);
	}
	
}

void GameUILayer::onRightTouch(Ref * obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
	{
		this->delegator->onRightButton(true);
	}
	else if (type == ui::Widget::TouchEventType::BEGAN)
	{
		this->delegator->onRightButton(false);
	}
}

void GameUILayer::onPauseTouch(cocos2d::Ref * obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		this->delegator->onPauseButton();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
	}
}

void GameUILayer::onChangePig( Ref * obj, ui::Widget::TouchEventType type )
{
	if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
	{

	}
	else if (type == ui::Widget::TouchEventType::BEGAN)
	{
		this->delegator->onChangeRole(Pig);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_CHANGE_CHARACTER);
	}
}

void GameUILayer::onChangeMonkey( Ref * obj, ui::Widget::TouchEventType type )
{
	if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
	{

	}
	else if (type == ui::Widget::TouchEventType::BEGAN)
	{
		this->delegator->onChangeRole(Monkey);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_CHANGE_CHARACTER);
	}
}

void GameUILayer::updateHP(int blood)
{
	ui::Widget* widgetUI = dynamic_cast<ui::Widget*>(getChildByTag(WIDGETUI_TAG));

	ui::ImageView* hp1 = (ui::ImageView*)(widgetUI->getChildByName("HP_1"));
	ui::ImageView* hp2 = (ui::ImageView*)(widgetUI->getChildByName("HP_2"));
	ui::ImageView* hp3 = (ui::ImageView*)(widgetUI->getChildByName("HP_3"));

	int hpMod = blood % 3;
	int hpNum = blood / 3;

	switch (hpNum)
	{
	case 0:
	{
		hp2->loadTexture("UI/blood_4.png");
		hp3->loadTexture("UI/blood_4.png");
		updateBloodMod(hpMod, hp1);
		break;
	}
	case 1:
	{
		hp1->loadTexture("UI/blood_1.png");
		hp3->loadTexture("UI/blood_4.png");
		updateBloodMod(hpMod, hp2);
		break;
	}
	case 2:
	{
		hp1->loadTexture("UI/blood_1.png");
		hp2->loadTexture("UI/blood_1.png");
		updateBloodMod(hpMod, hp3);
		break;
	}
	case 3:
	{
		hp1->loadTexture("UI/blood_1.png");
		hp2->loadTexture("UI/blood_1.png");
		hp3->loadTexture("UI/blood_1.png");
		break;
	}
	default:
		CCASSERT(0, "invaild hp");
		break;
	}
}

void GameUILayer::updateBloodMod(int mod, cocos2d::ui::ImageView * hp)
{
	switch (mod)
	{
	case 0:
		hp->loadTexture("UI/blood_4.png");
		break;
	case 1:
		hp->loadTexture("UI/blood_3.png");
		break;
	case 2:
		hp->loadTexture("UI/blood_2.png");
		break;
	default:
		CCASSERT(0, "invaild hp");
		break;
	}
}

void GameUILayer::onChangedRole(CallBackData * data)
{
	PlayerRoleChanged * roleData = dynamic_cast<PlayerRoleChanged*>(data);
	CCASSERT(roleData, "invaild Role data");

	ROLE r = roleData->r;

	switch (r)
	{
	case Monkey:
		m_icon_monkey->setPosition(m_firstPos);
		m_icon_pig->setPosition(m_secondPos);
		m_icon_pig->setScale(UI_ICON_SCALE_SMALL);
		m_icon_monkey->setScale(1);
		break;
	case Pig:
		m_icon_pig->setPosition(m_firstPos);
		m_icon_monkey->setPosition(m_secondPos);
		m_icon_monkey->setScale(UI_ICON_SCALE_SMALL);
		m_icon_pig->setScale(1);
		break;
	default:
		break;
	}
}

void GameUILayer::onPlayerDead(CallBackData * data)
{
	if (m_isSucc)
		return;

	if (!m_isEnter)
		return;

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_LOST);
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	m_lostUI = ResourceLoader::getInstance()->loadUIFromFile("Lost/Lost.ExportJson");
	m_lostUI->setTouchEnabled(false);
	addChild(m_lostUI, LOST_UI_ZORDER);

	m_actionObj = cocostudio::ActionManagerEx::getInstance()->playActionByName("Lost.ExportJson", "Lost");

	ui::Button * btnBack = (ui::Button*)m_lostUI->getChildByName("Button_Back");
	ui::Button * btnRestart = (ui::Button*)m_lostUI->getChildByName("Button_Restart");
	ui::Button* btnShare = (ui::Button*)m_lostUI->getChildByName("Button_Share");

	btnBack->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onBackTouch, this));
	btnRestart->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onRestartTouch, this));
	btnShare->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onShare, this));
}

void GameUILayer::onBackTouch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		if (m_actionObj)
		{
			m_actionObj->stop();
		}

		cocostudio::ActionManagerEx::destroyInstance();


		if(diciVector->size())
		{
			for(int i = 0;i<diciVector->size();i++)
				delete (*diciVector)[i];
			diciVector->clear();
		}

		auto newGameScene = MissionScene::create();
		TransitionScene *transition = TransitionFade::create(1, newGameScene);
		Director::getInstance()->replaceScene(transition);
		//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACK_TITLE, true);
	}
}

void GameUILayer::onRestartTouch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		if (m_actionObj)
		{
			m_actionObj->stop();
		}
		
		cocostudio::ActionManagerEx::destroyInstance();


		if(diciVector->size())
		{
			for(int i = 0;i<diciVector->size();i++)
				delete (*diciVector)[i];
			diciVector->clear();
		}

		auto newGameScene = GameScene::create();
		TransitionScene *transition = TransitionFade::create(1, newGameScene);
		Director::getInstance()->replaceScene(transition);
		//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACK_MISSION_1, true);
	}
}

void GameUILayer::enterSecondMap()
{
	m_actionObj->stop();
	cocostudio::ActionManagerEx::destroyInstance();

	if(diciVector->size())
	{
		for(int i = 0;i<diciVector->size();i++)
			delete (*diciVector)[i];
		diciVector->clear();
	}


	GameScene* secondGameScene = new GameScene(2);
	secondGameScene->init();
	TransitionScene *transition = TransitionFade::create(1, secondGameScene);
	Director::getInstance()->replaceScene(transition);
}


void GameUILayer::onShare(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		if (m_actionObj)
		{
			m_actionObj->stop();
			cocostudio::ActionManagerEx::destroyInstance();
			m_actionObj = NULL;
			NotDoneSprite * notObjc = NotDoneSprite::create(this);
		}
	}
}

void GameUILayer::setUIWidgetsEnable(bool enable)
{
	if (m_playUI)
		m_playUI->setEnabled(enable);

	if (m_lostUI)
		m_lostUI->setEnabled(enable);

	if (m_succUI)
		m_succUI->setEnabled(enable);
}

void GameUILayer::onNextMission(CallBackData * data)
{
	m_isSucc = true;
	MissionNumData * missionData = dynamic_cast<MissionNumData*>(data);
	CCASSERT(missionData, "invaild mission data");
	m_missionNum = missionData->missionNum;
	
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_NEXT_MISSION);
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	m_succUI = ResourceLoader::getInstance()->loadUIFromFile("Win/Win.ExportJson");
	m_succUI->setTouchEnabled(false);
	addChild(m_succUI, LOST_UI_ZORDER);

	m_actionObj = cocostudio::ActionManagerEx::getInstance()->playActionByName("Win.ExportJson", "Win");

	ui::Button * btnBack = (ui::Button*)m_succUI->getChildByName("Button_Back");
	ui::Button * btnNext = (ui::Button*)m_succUI->getChildByName("Button_Next");
	ui::Button* btnShare = (ui::Button*)m_succUI->getChildByName("Button_Share");

	btnBack->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onBackTouch, this));
	btnNext->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onNext, this));
	btnShare->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onShare, this));
}

void GameUILayer::onNext(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		if (m_actionObj)
		{
			m_actionObj->stop();
			m_actionObj = NULL;
		}

		cocostudio::ActionManagerEx::destroyInstance();


		if (diciVector->size())
		{
			for (int i = 0; i < diciVector->size(); i++)
				delete (*diciVector)[i];
			diciVector->clear();
		}

		if (m_missionNum == 2)
		{
			NotDoneSprite * notObjc = NotDoneSprite::create(this);
		}
		else
		{
			auto newGameScene = new GameScene(m_missionNum + 1);
			
			if (newGameScene->init())
			{
				newGameScene->autorelease();
				TransitionScene *transition = TransitionFade::create(1, newGameScene);
				Director::getInstance()->replaceScene(transition);
			}
			else
			{
				delete newGameScene;
				newGameScene = NULL;
			}
		}
	}
}

void GameUILayer::onEnter()
{
	Layer::onEnter();

	m_isEnter = true;
}


