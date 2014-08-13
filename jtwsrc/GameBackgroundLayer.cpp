//
//  GameBackgroundLayer.cpp
//  JTW
//
//  Created by alexzzp on 14-8-13.
//
//

#include "GameBackgroundLayer.h"

bool GameBackgroundLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	Sprite *background;
    background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_day"));
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	this->addChild(background);

	return true;
}

float GameBackgroundLayer::getLandHeight() {
    return Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"))->getContentSize().height;
}
