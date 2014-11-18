/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        AppDelegate.hpp
 *  Created Time:    2014/11/15  11:47:46
 *  Description:     
 *  Revision:
 *  License:
 */

#ifndef __APPDELEGATE__
#define __APPDELEGATE__ 1

#include "cocos2d.h"

NS_CC_BEGIN

/**
@brief    The cocos2d Application.
The reason for implement as private inheritance is to hide some interface call by Director.
*/
class AppDelegate:private Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
    
private:
    bool initGame();
    bool testDebug();
    bool testLogic();
};

NS_CC_END;

#endif
