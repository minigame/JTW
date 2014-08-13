#include "GameScene.h"
#include "GameBackgroundLayer.h"
#include "GamePlayerLayer.h"
#include "GameUILayer.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

bool GameScene::init(){
	if(Scene::initWithPhysics())
    {
        //this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
       this->getPhysicsWorld()->setGravity(Vect(0, -900));

        // Add the background
        //auto backgroundLayer = GameBackgroundLayer::create();
        //if(backgroundLayer) {
        //    this->addChild(backgroundLayer);
        //}

        //auto statusLayer = StatusLayer::create();

        // Add the main game layer
        auto gameLayer = GamePlayerLayer::create();
        if (gameLayer) {
            //gameLayer->setPhyWorld(this->getPhysicsWorld());
            //gameLayer->setDelegator(nullptr);
            this->addChild(gameLayer);
        }

        //// Add the game status layer to show the score and game status
        //if(statusLayer) {
            //this->addChild(statusLayer);
        //}

        // Add operation layer to control the game
        auto uiLayer = GameUILayer::create();
        if(uiLayer) {
            uiLayer->setDelegator(gameLayer);
            this->addChild(uiLayer);
        }

	 	return true;
	}
    else {
		return false;
	}
}

void GameScene::restart() {
    this->removeAllChildrenWithCleanup(true);
    this->init();
}
