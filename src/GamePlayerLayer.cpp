﻿#include "GamePlayerLayer.h"
#include "Helper.h"

GamePlayerLayer::GamePlayerLayer()
{
	m_world = NULL;
};

GamePlayerLayer::~GamePlayerLayer(){};

bool GamePlayerLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//get the origin point of the X-Y axis, and the visiable size of the screen
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	//create a bird and set the position in the center of the screen
	m_playerSprite = PlayerSprite::create();
	m_playerSprite->setPosition(Point(origin.x + visiableSize.width / 2, origin.y + visiableSize.height * 3 / 5 - 10));
	this->addChild(m_playerSprite);

	this->getScheduler()->scheduleUpdate(this,0,false);

	return true;
}

void GamePlayerLayer::onTouch()
{
	
}

void GamePlayerLayer::onLeftButton(bool isCancel)
{
	m_playerSprite->leftWalk(isCancel);
}

void GamePlayerLayer::onRightButton(bool isCancel)
{
	m_playerSprite->rightWalk(isCancel);
}

void GamePlayerLayer::onActionButton(bool isCancel)
{
	m_playerSprite->attack(isCancel);
}

void GamePlayerLayer::onJumpButton(bool isCancel)
{
	m_playerSprite->jump(isCancel);
}

void GamePlayerLayer::setPhyWorld(PhysicsWorld* world) 
{
	m_world = world;
}

void GamePlayerLayer::setBackLayer(GameBackgroundLayer* layer)
{
	m_backLayer = layer;
}

void GamePlayerLayer::update(float dt)
{
	Layer::update(dt);

	Point v = m_playerSprite->getPosition();
	setViewPointCenter(v);

}

void GamePlayerLayer::setViewPointCenter(Point position)
{
	Size winSize = Director::getInstance()->getWinSize();
	TMXTiledMap* _tileMap = m_backLayer->getTiledMap();

	LOGD(("winSize: " + ptoa(winSize.width, winSize.height) + "\n").c_str(), NULL);
	LOGD(("position: " + ptoa(position.x, position.y) + "\n").c_str(), NULL);

	// 防止玩家超出边界
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Point actualPosition = ccp(x, y);
	LOGD(("actualPosition: " + ptoa(actualPosition.x, actualPosition.y) + "\n").c_str(), NULL);

	Point centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	Point viewPoint = ccpSub(centerOfView, actualPosition);
	LOGD(("viewPoint: " + ptoa(viewPoint.x, viewPoint.y) + "\n\n").c_str(), NULL);
	m_backLayer->setPosition(viewPoint);
	this->setPosition(viewPoint);

}

