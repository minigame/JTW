//
//  GameBackgroundLayer.cpp
//  JTW
//
//  Created by alexzzp on 14-8-13.
//
//

#include "GameBackgroundLayer.h"
#include "ResourceMgr.h"
#include "PhyConst.h"

GameBackgroundLayer::GameBackgroundLayer(void)
{
	m_physicLayer = NULL;
	m_tileMap = NULL;
	m_isMapMove = true;
	m_world = NULL;
}

GameBackgroundLayer::~GameBackgroundLayer(void)
{

}

bool GameBackgroundLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	m_physicLayer = Sprite::create();

	if (m_physicLayer == NULL)
		return false;

	m_tileMap = TMXTiledMap::create("TileGameResources/TileMap.tmx");

	if (m_tileMap == NULL)
		return false;

	m_background = m_tileMap->getLayer("Background");
	m_foreground = m_tileMap->getLayer("Foreground");
	m_meta = m_tileMap->getLayer("Meta");
	m_meta->setVisible(false);
	this->addChild(m_tileMap);

	setViewPointCenter(Vec2(getContentSize().width / 2, getContentSize().height / 2));

	return true;
}

void GameBackgroundLayer::setViewPointCenter(Point position)
{
	if (m_lastPosition == position || !m_isMapMove)
		return;

	Size winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x + m_tileMap->getTileSize().width / 2, winSize.width / 2); 
	int y = MAX(position.y + m_tileMap->getTileSize().height / 2, winSize.height / 2); 
	x = MIN(x, (m_tileMap->getMapSize().width * m_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (m_tileMap->getMapSize().height * m_tileMap->getTileSize().height) - winSize.height / 2);
	Point actualPosition = Vec2(x, y);

	Point centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Point viewPoint = Vec2(centerOfView)- Vec2(actualPosition);
	this->setPosition(viewPoint);
	updatePhysic(viewPoint);
}

void GameBackgroundLayer::updatePhysic(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position);
}


Point GameBackgroundLayer::tileCoordForPosition(Point position)
{
	int x = position.x / m_tileMap->getTileSize().width;
	int y = ((m_tileMap->getMapSize().height * m_tileMap->getTileSize().height) - position.y) / m_tileMap->getTileSize().height;

	return Vec2(x, y);
}

void GameBackgroundLayer::setMapMoveEnable(bool enable)
{
	m_isMapMove = enable;
}

bool GameBackgroundLayer::getMapMoveEnable() const
{
	return m_isMapMove;
}

void GameBackgroundLayer::setPhyWorld(PhysicsWorld* world)
{
	m_world = world;
}

TMXTiledMap* GameBackgroundLayer::getTiledMap() const
{
	return m_tileMap;
}
