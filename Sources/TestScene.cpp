/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        TestScene.cpp
 *  Created Time:    2014/11/15  10:55:35
 *  Description:     测试scene
 *  Revision:
 */

#include "JTWInfoCenter.hpp"
#include "TestScene.hpp"

USING_NS_CC;

/* -------------------------------------------------- */
/* cocso2d framework */

TestScene::TestScene()
{

}

TestScene::~TestScene()
{

}

bool TestScene::init()
{
    if (Scene::init() == false) {
        return false;
    }

    // 初始化当前scene的基本信息
    JTWInfoCenterSig->loadSceneInfo();
 
    // 加载背景
    Sprite *sp = Sprite::create("background/TencentGame.png");
    if (sp) {
        sp->setAnchorPoint(Vec2(0, 0));
        sp->setPosition(Vec2(0, 0));
        // sp->setPosition(JTWInfoCenterSig->getSceenOrigin());

        auto screenSize = JTWInfoCenterSig->getSceenSize();
        auto scaleX = screenSize.width / sp->getTextureRect().size.width;
        auto scaleY = screenSize.height / sp->getTextureRect().size.height;
        sp->setScale(scaleX, scaleY);
        addChild(sp);
    }

    // if (initPhysics() == false) {
    //     return false ;
    // }

    return true;
}

/* -------------------------------------------------- */
/* application logic */

bool TestScene::initPhysics()
{
	if (this->initWithPhysics() == false) {
		return false;
    }
    return true;
}

bool TestScene::loadConfig()
{
    return true;
}


