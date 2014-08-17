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

		btnA->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onATouch, this));
		btnB->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onBTouch, this));
		btnleft->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onLeftTouch, this));
		btnright->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onRightTouch, this));

		return true;
	} else {
		return false;
	}
}


void GameUILayer::onATouch(cocos2d::Object* obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{

	}
	else
	{
		this->delegator->onActionButton();
	}
	
}

void GameUILayer::onBTouch(cocos2d::Object* obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		
	}
	else
	{
		this->delegator->onJumpButton();
	}
}

void GameUILayer::onLeftTouch(cocos2d::Object* obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		this->delegator->onNoAction();
	}
	else
	{
		this->delegator->onLeftButton();
	}
	
}

void GameUILayer::onRightTouch(cocos2d::Object* obj, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		this->delegator->onNoAction();
	}
	else
	{
		this->delegator->onRightButton();
	}
	
}
