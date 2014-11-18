/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        AppDelegate.cpp
 *  Created Time:    2014/11/15  11:49:21
 *  Description:     
 *  Revision:
 *  License:
 */

#include <iostream>

#include "GKResolution.hpp"

#include "TestScene.hpp"
#include "JTWResMng.hpp"

#include "AppDelegate.hpp"

USING_NS_CC;
USING_NS_STD;

/* -------------------------------------------------- */
/* constants */

#define SCREEN_WIDTH    (GK_RESOLUTION_IPHONE_5_WIDTH)
#define SCREEN_HEIGHT   (GK_RESOLUTION_IPHONE_5_HEIGHT)

// #define SCREEN_WIDTH    (GK_RESOLUTION_PHONE_REDMI_WIDTH)
// #define SCREEN_HEIGHT   (GK_RESOLUTION_PHONE_REDMI_HEIGHT)

/* -------------------------------------------------- */
/* cocso2d framework */

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{

}

bool AppDelegate::applicationDidFinishLaunching()
{
    bool ret;
    
    if (initGame() == false) {
        return false;
    }
    
    ret = testLogic();
    //ret = testDebug();

    return ret;
}

// This function will be called when the app is inactive. 
// When comes a phone call it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}

/* -------------------------------------------------- */
/* initialize logic */

bool AppDelegate::initGame()
{
    bool ret;
    ret = JTWResMngSig->loadConfigFile();
    return ret;
}

/* -------------------------------------------------- */
/* application logic */

bool AppDelegate::testDebug()
{
    cout<<(*JTWResMngSig->getConfigBasicMap())["helloLabel"]<<endl;
    cout<<(*JTWResMngSig->getConfigBasicMap())["worldGravity_x"]<<endl;
    cout<<(*JTWResMngSig->getConfigBasicMap())["worldGravity_y"]<<endl;
    return true;
}

bool AppDelegate::testLogic()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview   = director->getOpenGLView();
    if (glview == NULL) {
        glview = GLView::create("testview");
        director->setOpenGLView(glview);
    }
 
    // 注意多分辨率设计
    glview->setContentScaleFactor(2);
    glview->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, ResolutionPolicy::SHOW_ALL);
    // glview->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, ResolutionPolicy::NO_BORDER);

	glview->setFrameSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = TestScene::create();

    // run
    director->runWithScene(scene);
    return true;
}
