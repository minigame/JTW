#include "GameUILayer.h"
#include "CallBackMgr.h"
#include "MissionScene.h"
#include "GameScene.h"
USING_NS_CC;

GameUILayer::GameUILayer()
{
    LOGD("GameUILayer created");
	m_icon_pig = NULL;
	m_icon_monkey = NULL;
	m_actionObj = NULL;

    m_musicEnable = 1;
    m_previousVolume = 0.0;
}

GameUILayer::~GameUILayer()
{
    LOGD("GameUILayer destory");
	CallBackMgr::getInstance()->unRegisterFunction(PLAYER_ROLE_CHANGED, this);
	CallBackMgr::getInstance()->unRegisterFunction(PlAYER_DEAD, this);
}

bool GameUILayer::init()
{
	if (Layer::init())
	{
		cocostudio::ActionManagerEx::destroyInstance();
        ui::Widget* widget = ResourceLoader::getInstance()->loadUIFromFile("UI/UI1_1.ExportJson");
		addChild(widget);
		widget->setTag(WIDGETUI_TAG);

		ui::Button * btnA = (ui::Button*)widget->getChildByName("Button_A");
		ui::Button * btnB = (ui::Button*)widget->getChildByName("Button_B");
		ui::Button * btnleft = (ui::Button*)widget->getChildByName("Button_Left");
		ui::Button * btnright = (ui::Button*)widget->getChildByName("Button_Right");
		ui::Button * btnPause = (ui::Button*)widget->getChildByName("Button_Pause");
        
		m_icon_pig = (ui::ImageView*)widget->getChildByName("Icon_Pig");
		m_icon_monkey = (ui::ImageView*)widget->getChildByName("Icon_Monkey");
		ui::ImageView * HP_1 = (ui::ImageView*)widget->getChildByName("HP_1");
		ui::ImageView * HP_2 = (ui::ImageView*)widget->getChildByName("HP_2");
		ui::ImageView * HP_3 = (ui::ImageView*)widget->getChildByName("HP_3");

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
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
    } 
	else if (keyCode == EventKeyboard::KeyCode::KEY_D ) 
	{
        this->delegator->onRightButton(false);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
    } 
	else if (keyCode == EventKeyboard::KeyCode::KEY_J ) 
	{
        this->delegator->onActionButton(false);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
    } 
	else if (keyCode == EventKeyboard::KeyCode::KEY_K) 
	{
        this->delegator->onJumpButton(false);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
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
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
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
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
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
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
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
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AUDIO_BUTTON_CLICK);
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
	if(blood == 0)   //这个是没有血
	{
		((ui::ImageView*)(widgetUI->getChildByName("HP_1")))->setVisible(false);
		((ui::ImageView*)(widgetUI->getChildByName("HP_2")))->setVisible(false);
		((ui::ImageView*)(widgetUI->getChildByName("HP_3")))->setVisible(false);
	}
	else if(blood == 1)
	{
		((ui::ImageView*)(widgetUI->getChildByName("HP_1")))->setVisible(true);
		((ui::ImageView*)(widgetUI->getChildByName("HP_2")))->setVisible(false);
		((ui::ImageView*)(widgetUI->getChildByName("HP_3")))->setVisible(false);
	}
	else if(blood == 2)
	{
		((ui::ImageView*)(widgetUI->getChildByName("HP_1")))->setVisible(true);
		((ui::ImageView*)(widgetUI->getChildByName("HP_2")))->setVisible(true);
		((ui::ImageView*)(widgetUI->getChildByName("HP_3")))->setVisible(false);
	}
	else if(blood == 3)
	{
		((ui::ImageView*)(widgetUI->getChildByName("HP_1")))->setVisible(true);
		((ui::ImageView*)(widgetUI->getChildByName("HP_2")))->setVisible(true);
		((ui::ImageView*)(widgetUI->getChildByName("HP_3")))->setVisible(true);
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
	ui::Widget * widget = ResourceLoader::getInstance()->loadUIFromFile("Lost/Lost.ExportJson");
	addChild(widget, 1000);

	m_actionObj = cocostudio::ActionManagerEx::getInstance()->playActionByName("Lost.ExportJson", "Lost");

	ui::Button * btnBack = (ui::Button*)widget->getChildByName("Button_Back");
	ui::Button * btnRestart = (ui::Button*)widget->getChildByName("Button_Restart");
	ui::Button* btnShare = (ui::Button*)widget->getChildByName("Button_Share");

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
		m_actionObj->stop();
		cocostudio::ActionManagerEx::destroyInstance();
		auto newGameScene = MissionScene::create();
		TransitionScene *transition = TransitionFade::create(1, newGameScene);
		Director::getInstance()->replaceScene(transition);
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
		m_actionObj->stop();
		cocostudio::ActionManagerEx::destroyInstance();
		auto newGameScene = GameScene::create();
		TransitionScene *transition = TransitionFade::create(1, newGameScene);
		Director::getInstance()->replaceScene(transition);
	}
}

void GameUILayer::enterSecondMap()
{
	m_actionObj->stop();
	cocostudio::ActionManagerEx::destroyInstance();
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
		}
	}
}
