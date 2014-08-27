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
#include "Tag.h"

GameBackgroundLayer::GameBackgroundLayer(void)
{
	//m_physicLayer = NULL;
	m_tileMap = NULL;
	m_isMapMove = true;
	m_world = NULL;
}

GameBackgroundLayer::~GameBackgroundLayer(void)
{
	m_gears;
}

bool GameBackgroundLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	/*m_physicLayer = Sprite::create();

	if (m_physicLayer == NULL)
		return false;*/

	//setViewPointCenter(Vec2(getContentSize().width / 2, getContentSize().height / 2));

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

bool GameBackgroundLayer::setTiledMap(TMXTiledMap* tiledMap)
{
	m_tileMap = tiledMap;

	if (m_tileMap == NULL)
		return false;

	m_background = m_tileMap->getLayer("background");
	//m_foreground = m_tileMap->getLayer("foreground");
	m_physics = m_tileMap->objectGroupNamed("physics");
	m_gear = m_tileMap->objectGroupNamed("gear");
	if (m_physics == NULL)
		return false;

	readGearAttributes();
	buildGears();
	buildMapByPhyBoxes();
	this->addChild(m_tileMap);
	return true;
}

bool GameBackgroundLayer::setTiledMap(string path)
{
	LOGD((path+"\n").c_str(), NULL);
	return this->setTiledMap(TMXTiledMap::create(path));
}

void GameBackgroundLayer::buildGears()
{
	for (int i = 0; i < m_gearCount; i++)
	{
		if (m_gears[i].type == GEAR_BRIDGE)
		{
			BridgeSprite * bridge = BridgeSprite::create();
			m_obstacleLayer->addChild(bridge);
			bridge->setPosition(Point(m_gears[i].position.x, m_gears[i].position.y + 220));
		}
	}
}

void GameBackgroundLayer::buildMapByPhyBoxes()
{
	ValueVector objects = m_physics->getObjects();
	for (Value object : objects)
	{
		ValueMap dict = object.asValueMap();
		int x = dict["x"].asInt();
		int y = dict["y"].asInt();
		int width = dict["width"].asInt();
		int height = dict["height"].asInt();
		createPhyBox(Point(x + width / 2, y + height / 2), Size(width, height));
	}
}

void GameBackgroundLayer::readGearAttributes()
{
	ValueVector objects = m_gear->getObjects();
	m_gearCount = objects.size();
	m_gears = new GearAttribute[m_gearCount];
	int i = 0;
	for (Value object : objects)
	{
		ValueMap dict = object.asValueMap();
		m_gears[i].position = Point(0, 0);
		m_gears[i].position = Point(dict["x"].asInt(), dict["y"].asInt());
		m_gears[i].coord = tileCoordForPosition(m_gears[i].position);
		m_gears[i].period = 0;
		m_gears[i].period = dict["period"].asInt();
		m_gears[i].stop = 0;
		m_gears[i].stop = dict["stop"].asInt();
		string type = dict["type"].asString();
		if (type.compare("bridge") == 0)
			m_gears[i].type = GEAR_BRIDGE;
		else if (type.compare("lift") == 0)
			m_gears[i].type = GEAR_LIFT;
		else if (type.compare("door") == 0)
			m_gears[i].type = GEAR_DOOR;
		else if (type.compare("boom") == 0)
			m_gears[i].type = GEAR_BOOM;
		else if (type.compare("stone") == 0)
			m_gears[i].type = GEAR_STONE;
		else
			m_gears[i].type = GEAR_OBJECT;
		string direction = dict["direction"].asString();
		if (direction.compare("up") == 0)
			m_gears[i].direction = GEAR_UP;
		else if (direction.compare("down") == 0)
			m_gears[i].direction = GEAR_DOWN;
		else if (direction.compare("left") == 0)
			m_gears[i].direction = GEAR_LEFT;
		else if (direction.compare("right") == 0)
			m_gears[i].direction = GEAR_RIGHT;
		else
			m_gears[i].direction = GEAR_STATIC;
		i++;
	}
}

/*void GameBackgroundLayer::buildMapByPhyBoxes()
{
	int width = m_tileMap->getMapSize().width;
	int height = m_tileMap->getMapSize().height;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int tileGid = m_foreground->tileGIDAt(Point(i, j));
			if (tileGid)
			{
				Value properties = m_tileMap->propertiesForGID(tileGid);
				ValueMap map = properties.asValueMap();
				if (map["block"].asBool())
				{
					createPhyBox(positionForTileCoord(Point(i, j)), m_tileMap->getTileSize());
				}
			}
		}
	}
}*/

void GameBackgroundLayer::createPhyBox(Point position, Size size)
{
	auto sprite = Sprite::create();
	auto body = PhysicsBody::createBox(size);

	body->setCategoryBitmask(GROUND_CATEGORYBITMASK);
	body->setContactTestBitmask(GROUND_CONTACTTESTBITMASK);
	body->setCollisionBitmask(GROUND_COLLISIONBITMASK);
	body->setDynamic(false);
	sprite->setPosition(position);
	sprite->setPhysicsBody(body);
    sprite->setTag(BACKGROUND_TAG);
	this->addChild(sprite);
}

Point GameBackgroundLayer::tileCoordForPosition(Point position)
{
	int x = position.x / m_tileMap->getTileSize().width;
	int y = ((m_tileMap->getMapSize().height * m_tileMap->getTileSize().height) - position.y) / m_tileMap->getTileSize().height;

	return Point(x, y);
}

Point GameBackgroundLayer::positionForTileCoord(Point tileCoord)
{
	int x = tileCoord.x * m_tileMap->getTileSize().width + m_tileMap->getTileSize().width / 2;
	int y = m_tileMap->getMapSize().height * m_tileMap->getTileSize().height - (tileCoord.y * m_tileMap->getTileSize().height + m_tileMap->getTileSize().height / 2);

	return Point(x, y);
}

void GameBackgroundLayer::setObstacleLayer(GameObstacleLayer* layer)
{
	m_obstacleLayer = layer;
}

