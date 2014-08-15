//
//  GameBackgroundLayer.cpp
//  JTW
//
//  Created by alexzzp on 14-8-13.
//
//

#include "GameBackgroundLayer.h"
#include "ResourceMgr.h"

GameBackgroundLayer::GameBackgroundLayer(void)
{

}

GameBackgroundLayer::~GameBackgroundLayer(void)
{

}

bool GameBackgroundLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	Sprite *background;
    background = Sprite::createWithSpriteFrame(ResourceMgr::getInstance()->getImage("Map"));
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	this->addChild(background);

	return true;
}

float GameBackgroundLayer::getLandHeight() {
	return Sprite::createWithSpriteFrame(ResourceMgr::getInstance()->getImage("Map.png"))->getContentSize().height;
}
