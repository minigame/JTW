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
		auto dispatcher = Director::getInstance()->getEventDispatcher();
        auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(GameUILayer::onTouchesBegan, this);
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		return true;
	} else {
		return false;
	}
}

void GameUILayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
	this->delegator->onTouch();
}
