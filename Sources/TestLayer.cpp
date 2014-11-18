/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        TestLayer.cpp
 *  Created Time:    2014/11/16  00:55:32
 *  Description:     
 *  Revision:
 *  License:
 */

#include "JTWInfoCenter.hpp"
#include "TestLayer.hpp"

USING_NS_CC;

/* -------------------------------------------------- */
/* cocso2d framework */

TestLayer::TestLayer()
{

}

TestLayer::~TestLayer()
{

}

bool TestLayer::init()
{
    if (Layer::init() == false) {
        return false;
    }
    
    // 加载背景
    mBackground = Sprite::create("background/TencentGame.png");
    if (mBackground) {
        mBackground->setAnchorPoint(Vec2(0, 0));
        mBackground->setPosition(Vec2(0, 0));
        // mBackground->setPosition(JTWInfoCenterSig->getSceenOrigin());
        
        // auto screenSize = JTWInfoCenterSig->getSceenSize();
        // auto scaleX = screenSize.width / mBackground->getTextureRect().size.width;
        // auto scaleY = screenSize.height / mBackground->getTextureRect().size.height;
        // mBackground->setScale(scaleX, scaleY);
        addChild(mBackground);
    }
    
    return true;
}

/* -------------------------------------------------- */
/* application logic */
//
//void TestLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
//{
//    
//}


