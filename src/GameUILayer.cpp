//
//  OptionLayer.cpp
//  parasite-city
//
//  Created by Zhou.Zeyong on 14-2-18.
//
//

#include "GameUILayer.h"

GameUILayer::GameUILayer()
{}

GameUILayer::~GameUILayer()
{}

bool GameUILayer::init()
{
	if(Layer::init()){

		ui::Widget* widget = ResourceLoader::getInstance()->loadUIFromFile("JTW_UI/JTW_UI_1.ExportJson");
		addChild(widget);

		ui::Button * btnA = (ui::Button*)widget->getChildByName("Button_A");
		ui::Button * btnB = (ui::Button*)widget->getChildByName("Button_B");
		ui::Button * btnleft = (ui::Button*)widget->getChildByName("Button_Left");
		ui::Button * btnright = (ui::Button*)widget->getChildByName("Button_Right");

		btnA->setOpacity(128);
		btnB->setOpacity(128);
		btnleft->setOpacity(128);
		btnright->setOpacity(128);

		btnA->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onATouch, this));
		btnB->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onBTouch, this));
		btnleft->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onLeftTouch, this));
		btnright->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onRightTouch, this));

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
void GameUILayer::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        this->delegator->onLeftButton(false);
    } else if (keyCode == EventKeyboard::KeyCode::KEY_D ) {
        this->delegator->onRightButton(false);
    } else if (keyCode == EventKeyboard::KeyCode::KEY_J ) {
        this->delegator->onActionButton(false);
    } else if (keyCode == EventKeyboard::KeyCode::KEY_K) {
        this->delegator->onJumpButton(false);
    }
}

void GameUILayer::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
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

void GameUILayer::onATouch(cocos2d::Object* obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
	{
		this->delegator->onActionButton(true);
	}
	else
	{
		this->delegator->onActionButton(false);
	}
	
}

void GameUILayer::onBTouch(cocos2d::Object* obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
	{
		this->delegator->onJumpButton(true);
	}
	else
	{
		this->delegator->onJumpButton(false);
	}
}

void GameUILayer::onLeftTouch(cocos2d::Object* obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
	{
		this->delegator->onLeftButton(true);
	}
	else
	{
		this->delegator->onLeftButton(false);
	}
	
}

void GameUILayer::onRightTouch(cocos2d::Object* obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
	{
		this->delegator->onRightButton(true);
	}
	else
	{
		this->delegator->onRightButton(false);
	}
	
}
