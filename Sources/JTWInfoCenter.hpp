/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        JTWInfoCenter.hpp
 *  Created Time:    2014/11/15  17:53:07
 *  Description:     游戏过程中一些通用的数据存储的地方
 *  Revision:
 *  License:
 */

#ifndef __JTWINFOCENTER__
#define __JTWINFOCENTER__ 1

#include "cocos2d.h"

#include "GKSingleton.hpp"

NS_CC_BEGIN

class JTWInfoCenter
{
public:
    JTWInfoCenter();
    ~JTWInfoCenter();

// public interface function
public:
    int loadSceneInfo();

// private helper function
private:

// properties
    CC_SYNTHESIZE(Size, mSceenSize,   SceenSize);
    CC_SYNTHESIZE(Vec2, mSceenOrigin, SceenOrigin);

// private members
private:

};

typedef GKSingleton<JTWInfoCenter> JTWInfoCenterSingleton;
#define JTWInfoCenterSig (JTWInfoCenterSingleton::Instance())

NS_CC_END;

#endif
