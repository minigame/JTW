/*
 *  Copyright(c), All rights reserved.
 *  Author:          coreyzhu@tencent.com
 *  Filename:        testScene.cpp
 *  Created Time:    2014/08/28  21:48:47
 *  Description:     
 *  Revision:
 */

#include "Log.h"
#include "testScene.h"
#include "ResourceLoader.h"

USING_NS_CC;

/* ---------- testLayer ---------- */

class testLayer: public Layer
{
public:
	testLayer();
	~testLayer();
    
    bool init();
	CREATE_FUNC(testLayer);
    
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);

    void keyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void keyReleased(EventKeyboard::KeyCode keyCode, Event *event);
};

void testLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
    LOGD("receive a touch event");
}

testLayer::testLayer()
{
    LOGD("testlayer is created");
}

testLayer::~testLayer()
{
    //Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    //this->getEventDispatcher()->removeAllEventListeners();
    LOGD("testlayer is released");
}

bool testLayer::init()
{
	if (!Layer::init())
        return false;
    
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(testLayer::keyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(testLayer::keyReleased, this);
    //this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(testLayer::onTouchesBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void testLayer::keyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
    LOGD("key is pressed");
}

void testLayer::keyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    LOGD("key is released");
}

/* ---------- testScene ---------- */

testScene::testScene()
{
    LOGD("testScene is created");
}

testScene::~testScene()
{
    LOGD("testScene is destory");
}

bool testScene::init()
{
	if (!Scene::init())
        return false;
    
    // TOASK: 这里开启了下面的widget，下面的testLayer就接收不到touch事件
    ui::Widget* widget = ResourceLoader::getInstance()->loadUIFromFile("StartMenu/StartMenu.ExportJson");
	this->addChild(widget);

    Layer * aTestLayer = testLayer::create();
    this->addChild(aTestLayer);

    return true;
}

void testScene::onEnter()
{
	Scene::onEnter();
    this->scheduleOnce(schedule_selector(testScene::changeScene), 5);
    LOGD("try to change scene, ok");
}

void testScene::onExit()
{
    Scene::onExit();
    LOGD("testScene is exit");
}

void testScene::changeScene(float dt)
{
    LOGD("testScene is about to change the scene");
    auto scene = testScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}
