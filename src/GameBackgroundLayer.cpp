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
#include "DiCiData.h"

extern Point playerStart;
extern std::vector<Point>* monster1Vector;
extern std::vector<Point>* monster2Vector;
extern std::vector<Point>* bossVector;
extern std::vector<DiCiData*>* diciVector;

GameBackgroundLayer::GameBackgroundLayer(void)
{
	//m_physicLayer = NULL;
	m_tileMap = NULL;
	m_isMapMove = true;
	m_world = NULL;
	m_gears = NULL;
	m_gear = NULL;
	m_player = NULL;
	m_physics = NULL;
	m_obstacleLayer = NULL;
}

GameBackgroundLayer::~GameBackgroundLayer(void)
{
	//m_gears;
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
	m_player = m_tileMap->objectGroupNamed("player");
	if (m_physics == NULL)
		return false;

	readGearAttributes();
	buildGears();
	buildPlayers();
	buildMapByPhyBoxes();
	this->addChild(m_tileMap);
	return true;
}

bool GameBackgroundLayer::setTiledMap(string path)
{
	LOGD((path+"\n").c_str(), NULL);
	return this->setTiledMap(TMXTiledMap::create(path));
}

void GameBackgroundLayer::buildPlayers()
{
	ValueVector objects = m_player->getObjects();
	monster1Vector->clear();
	monster2Vector->clear();
	bossVector->clear();
	for (Value object : objects)
	{
		ValueMap dict = object.asValueMap();
		string type = dict["type"].asString();
		LOGD((type + " get!!!\n").c_str(), NULL);
		if (type.compare("start") == 0)
		{
			playerStart = Point(dict["x"].asInt(), dict["y"].asInt());
		}
		else if (type.compare("monster_1") == 0)
		{
			monster1Vector->push_back(Point(dict["x"].asInt(), dict["y"].asInt()));
		}
		else if (type.compare("monster_2") == 0)
		{
			monster2Vector->push_back(Point(dict["x"].asInt(), dict["y"].asInt()));
		}
		else if (type.compare("boss") == 0)
		{
			bossVector->push_back(Point(dict["x"].asInt(), dict["y"].asInt()));
		}
	}
}

void GameBackgroundLayer::buildGears()
{
	diciVector->clear();
	int f = 30;
	int tile_offset = 30;
	int gate_offset_down = 219;
	int gate_offset_top = -159;
	Size hurt_margin = Size(0, 0);
	for (int i = 0; i < m_gearCount; i++)
	{
		if (m_gears[i].type == GEAR_BRIDGE)
		{
			BridgeSprite * bridge = BridgeSprite::create();
			bridge->setPosition(Point(m_gears[i].position.x + tile_offset, m_gears[i].position.y + gate_offset_down));
			m_obstacleLayer->addChild(bridge);
		}
		else if (m_gears[i].type == GEAR_LIFT)
		{
			ElevatorSprite * lift = ElevatorSprite::create();
			lift->setOriginPosition(Point(m_gears[i].position.x + tile_offset, m_gears[i].position.y + tile_offset));
			lift->setReturnLength(m_gears[i].distance);
			switch (m_gears[i].direction)
			{
			case GEAR_UP:
				lift->setSpeed(m_gears[i].speed);
				lift->setDirection(UpAndDown);
				break;
			case GEAR_DOWN:
				lift->setSpeed(-m_gears[i].speed);
				lift->setDirection(UpAndDown);
				break;
			case GEAR_LEFT:
				lift->setSpeed(-m_gears[i].speed);
				lift->setDirection(LeftAndRight);
				break;
			case GEAR_RIGHT:
				lift->setSpeed(m_gears[i].speed);
				lift->setDirection(LeftAndRight);
				break;
			default:
				lift->setSpeed(0);
				lift->setDirection(LeftAndRight);
			}
			lift->setTag(ELEVATOR_TAG);
			m_obstacleLayer->addChild(lift);
		}
		else if (m_gears[i].type == GEAR_DOOR)
		{
			int gate_offset_temp = 0;
			GateSprite* gate = GateSprite::create();
			switch (m_gears[i].direction_self)
			{
			case GEAR_UP:
				gate->setGateRunStatus(GateStatus::Rotate);
				gate->setZhouDir(ZHOUDIR::Top);
				gate_offset_temp = gate_offset_top;
				break;
			case GEAR_DOWN:
				gate->setGateRunStatus(GateStatus::Rotate);
				gate->setZhouDir(ZHOUDIR::Down);
				gate_offset_temp = gate_offset_down;
				break;
			case GEAR_LEFT:
				gate->setGateRunStatus(GateStatus::Line);
				gate->setZhouDir(ZHOUDIR::Top);
				gate_offset_temp = gate_offset_top;
				break;
			case GEAR_RIGHT:
			default:
				gate->setGateRunStatus(GateStatus::Line);
				gate->setZhouDir(ZHOUDIR::Down);
				gate_offset_temp = gate_offset_down;
			}
			switch (m_gears[i].direction)
			{
			/*case GEAR_UP:
			case GEAR_DOWN:*/
			case GEAR_LEFT:
				gate->setDir(0);
				break;
			case GEAR_RIGHT:
			default:
				gate->setDir(1);
			}
			gate->setTotalMove(m_gears[i].offset);
			gate->setDetaMove(m_gears[i].speed / f);
			gate->setTimePerMove(1.0f / f);
			gate->setMoveRange(m_gears[i].distance);
			gate->setPosition(Point(m_gears[i].position.x + tile_offset, m_gears[i].position.y + gate_offset_temp));
			gate->setTotalMove(m_gears[i].offset);
			gate->startRun();
			m_obstacleLayer->addChild(gate);
		}
		else if (m_gears[i].type == GEAR_BOOM)
		{
			FortSprite * boom = FortSprite::create();
			switch (m_gears[i].direction)
			{
			/*case GEAR_UP:
				boom->setDir(FortSpriteDirection::up);
				break;
			case GEAR_DOWN:
				boom->setDir(FortSpriteDirection::right);
				break;*/
			case GEAR_LEFT:
				boom->setDir(FortSpriteDirection::left);
				break;
			case GEAR_RIGHT:
				boom->setDir(FortSpriteDirection::right);
				break;
			default:
				boom->setDir(FortSpriteDirection::left);
			}
			boom->setPosition(Point(m_gears[i].position.x + tile_offset, m_gears[i].position.y + tile_offset));
			boom->shootOnTimer(m_gears[i].period, m_gears[i].count, m_gears[i].speed);
			m_obstacleLayer->addChild(boom);
		}
		else if (m_gears[i].type == GEAR_STONE)
		{
			StoneSprite * stone = StoneSprite::create();
			stone->setPosition(Point(m_gears[i].position.x + tile_offset, m_gears[i].position.y + tile_offset));
			m_obstacleLayer->addChild(stone);
		}
		else if (m_gears[i].type == GEAR_HURT)
		{
			diciVector->push_back(new DiCiData(Point(m_gears[i].position.x + m_gears[i].size.width / 2, m_gears[i].position.y + m_gears[i].size.height / 2), m_gears[i].size - hurt_margin, m_gears[i].direction));
			/*char log[100];
			sprintf(log, "pos: %f %f; size: %f %f; new_pos: %f %f; new_size: %f %f\n", m_gears[i].position.x, m_gears[i].position.y, m_gears[i].size.width, m_gears[i].size.height, m_gears[i].position.x + m_gears[i].size.width / 2, m_gears[i].position.y + m_gears[i].size.height / 2, (m_gears[i].size - hurt_margin).width, (m_gears[i].size - hurt_margin).height);
			LOGD(log, NULL);*/
		}
		else
		{
			LOGD("NOTHING!!!\n", NULL);
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
		string type = dict["type"].asString();
		//LOGD((type+" get!!!\n").c_str(), NULL);
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
		else if (type.compare("hurt") == 0)
			m_gears[i].type = GEAR_HURT;
		else
			m_gears[i].type = GEAR_OBJECT;
		m_gears[i].position = Point(dict["x"].asInt(), dict["y"].asInt());
		m_gears[i].coord = tileCoordForPosition(m_gears[i].position);
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
		string direction_self = dict["direction_self"].asString();
		if (direction_self.compare("up") == 0)
			m_gears[i].direction_self = GEAR_UP;
		else if (direction_self.compare("down") == 0)
			m_gears[i].direction_self = GEAR_DOWN;
		else if (direction_self.compare("left") == 0)
			m_gears[i].direction_self = GEAR_LEFT;
		else if (direction_self.compare("right") == 0)
			m_gears[i].direction_self = GEAR_RIGHT;
		else
			m_gears[i].direction_self = GEAR_STATIC;
		m_gears[i].speed = dict["speed"].asInt();
		m_gears[i].period = dict["period"].asInt();
		m_gears[i].count = dict["count"].asInt();
		m_gears[i].distance = dict["distance"].asInt();
		m_gears[i].offset = dict["offset"].asInt();
		m_gears[i].size = Size(dict["width"].asInt(), dict["height"].asInt());
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

