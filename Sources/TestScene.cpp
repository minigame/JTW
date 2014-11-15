/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        TestScene.cpp
 *  Created Time:    2014/11/15  10:55:35
 *  Description:     测试scene
 *  Revision:
 */

USING_NS_CC;

/* -------------------------------------------------- */
/* cocso2d framework */

TestScene::TestScene()
{

}

TestScene::~TestScene()
{

}

bool TestScene::init()
{
    if (Scene::init() == false) {
        return false;
    }

    JTWInfoCenterSig->loadSceneInfo();

    // if (initPhysics() == false) {
    //     return false ;
    // }

    return true;
}

/* -------------------------------------------------- */
/* application logic */

bool TestScene::initPhysics()
{
	if (this->initWithPhysics() == false) {
		return false;
    }
    return true;
}

bool TestScene::loadConfig()
{


}


