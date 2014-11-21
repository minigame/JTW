/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        JTWInfoCenter.cpp
 *  Created Time:    2014/11/15  17:53:07
 *  Description:     游戏过程中一些通用的数据存储的地方
 *  Revision:
 *  License:
 */


#include "JTWInfoCenter.hpp"

USING_NS_CC;

/* -------------------------------------------------- */
/* cocso2d framework */

JTWInfoCenter::JTWInfoCenter()
{
    mSceenSize.width  = 0;
    mSceenSize.height = 0;

    mSceenOrigin.x = 0;
    mSceenOrigin.y = 0;
}

JTWInfoCenter::~JTWInfoCenter()
{

}

/* -------------------------------------------------- */
/* scene logic */

int JTWInfoCenter::loadSceneInfo()
{
	mSceenSize   = Director::getInstance()->getVisibleSize();
	mSceenOrigin = Director::getInstance()->getVisibleOrigin();
    return 0;
}


