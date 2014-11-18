/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        TestLayer.hpp
 *  Created Time:    2014/11/16  00:55:32
 *  Description:     
 *  Revision:
 *  License:
 */

#ifndef __TESTLAYER__
#define __TESTLAYER__ 1

#include "cocos2d.h"

NS_CC_BEGIN

class TestLayer: public Layer
{
public:
    TestLayer();
    ~TestLayer();

    virtual bool init();
    CREATE_FUNC(TestLayer);

// public interface function
public:

// private helper function
private:
    
// private members
private:
    Sprite *mBackground;
};

NS_CC_END;

#endif
