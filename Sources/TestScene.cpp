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

    if (initPhysics() == false) {
        return false ;
    }


    return true;
}

/* -------------------------------------------------- */
/* application logic */

int TestScene::initPhysics()
{
	if (this->initWithPhysics() == false) {
		return false;
    }

	m_contactListener = EventListenerPhysicsContact::create();
	m_contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	m_contactListener->onContactSeperate = CC_CALLBACK_1(GameScene::onContactSeperate, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_contactListener, this);

	//getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	this->getPhysicsWorld()->setGravity(Vec2(DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("worldGravity_X")),
		DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("worldGravity_Y"))));
    
    return 0;
}






