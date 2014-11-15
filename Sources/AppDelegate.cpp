/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        AppDelegate.cpp
 *  Created Time:    2014/11/15  11:49:21
 *  Description:     
 *  Revision:
 *  License:
 */

#include "GKResolution.hpp"

#include "AppDelegate.hpp"
#include "TestScene.hpp"

USING_NS_CC;

/* -------------------------------------------------- */
/* constants */

#define SCREEN_WIDTH    (GK_RESOLUTION_IPHONE_5_WIDTH)
#define SCREEN_HEIGHT   (GK_RESOLUTION_IPHONE_5_HEIGHT)

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
    return testLogic();
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
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
/* application logic */

bool AppDelegate::testLogic()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview   = director->getOpenGLView();
    if (glview != NULL) {
        glview = GLView::create("testview");
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, ResolutionPolicy::SHOW_ALL);
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
