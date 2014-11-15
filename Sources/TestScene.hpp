/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        TestScene.cpp
 *  Created Time:    2014/11/15  11:06:59
 *  Description:     
 *  Revision:
 */

#ifndef __TESTSCENE__
#define __TESTSCENE__ 1

#include "cocos2d.h"

NS_CC_BEGIN

class TestScene: public Scene
{
public:
    TestScene();
    ~TestScene();

	virtual bool init();
	CREATE_FUNC(TestScene);

// public interface function
public:

// private helper function
private:
    bool initPhysics();

// private members
private:
};

NS_CC_END;

#endif
