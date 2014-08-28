#include "GameUILayer.h"
#include "CallBackMgr.h"
USING_NS_CC;

GameUILayer::GameUILayer()
{
    LOGD("GameUILayer created");
}

GameUILayer::~GameUILayer()
{
    LOGD("GameUILayer destory");
    this->getEventDispatcher()->removeAllEventListeners();
}

bool GameUILayer::init()
{
	if (Layer::init()) {
//        ui::Widget* widget = ResourceLoader::getInstance()->m_uiWidget;
        ui::Widget* widget = ResourceLoader::getInstance()->loadUIFromFile("UI/UI1_1.ExportJson");
		addChild(widget);
		widget->setTag(WIDGETUI_TAG);

		ui::Button * btnA = (ui::Button*)widget->getChildByName("Button_A");
		ui::Button * btnB = (ui::Button*)widget->getChildByName("Button_B");
		ui::Button * btnleft = (ui::Button*)widget->getChildByName("Button_Left");
		ui::Button * btnright = (ui::Button*)widget->getChildByName("Button_Right");
		ui::Button * btnPause = (ui::Button*)widget->getChildByName("Button_Pause");
        
		ui::ImageView * icon_pig = (ui::ImageView*)widget->getChildByName("Icon_Pig");
		ui::ImageView * icon_monkey = (ui::ImageView*)widget->getChildByName("Icon_Monkey");
		ui::ImageView * HP_1 = (ui::ImageView*)widget->getChildByName("HP_1");
		ui::ImageView * HP_2 = (ui::ImageView*)widget->getChildByName("HP_2");
		ui::ImageView * HP_3 = (ui::ImageView*)widget->getChildByName("HP_3");

		btnA->setOpacity(128);
		btnB->setOpacity(128);
		btnleft->setOpacity(128);
		btnright->setOpacity(128);

		btnA->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onATouch, this));
		btnB->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onBTouch, this));
		btnleft->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onLeftTouch, this));
		btnright->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onRightTouch, this));
		btnPause->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onPauseTouch, this));

		icon_pig->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onChangePig, this));
		icon_monkey->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onChangeMonkey, this));

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
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_I)
	{
		this->delegator->onChangeRole(Pig);
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
