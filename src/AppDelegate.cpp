﻿
#include "AppDelegate.h"
#include "LoadingScene.h"

#include "DiCiData.h"
#include <vector>
vector<DiCiData*>* diciVector;

using namespace std;
USING_NS_CC;

AppDelegate::AppDelegate() {
    // 建立全局使用的vector
    diciVector = new vector<DiCiData*>();
}

AppDelegate::~AppDelegate() 
{
	CocosDenshion::SimpleAudioEngine::getInstance()->end();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("JTW");
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
	glview->setFrameSize(1280, 720);

    // turn on display FPS
#if defined(DEBUG)
    director->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = LoadingScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
