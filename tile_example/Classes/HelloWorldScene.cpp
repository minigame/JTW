#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    
	// 加载地图
	_tileMap = TMXTiledMap::create("../Resources/TileGameResources/TileMap.tmx");
	_background = _tileMap->layerNamed("Background"); // 背景层
	_foreground = _tileMap->layerNamed("Foreground"); // 物品层
	_meta = _tileMap->layerNamed("Meta"); //物理层
	_meta->setVisible(false);
	this->addChild(_tileMap);

	// 加载玩家
	TMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");
	if (!objectGroup)
	{
		return false;
	}
	ValueMap spawnPoint = objectGroup->objectNamed("SpawnPoint");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	_player = Sprite::create("../Resources/TileGameResources/Player.png");
	_player->setPosition(ccp(x, y));
	this->addChild(_player);
	this->setViewPointCenter(_player->getPosition());

	// 触控处理
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::ccTouchesBegan, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::ccTouchesEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->setTouchEnabled(true);
	
	return true;
}

void HelloWorld::setViewPointCenter(Point position)
{
	Size winSize = Director::sharedDirector()->getWinSize();

	// 防止玩家超出边界
	int x = MAX(position.x + _tileMap->getTileSize().width / 2, winSize.width / 2); // position.x增加_tileMap->getTileSize().width的一半是为了防止出现黑线
	int y = MAX(position.y + _tileMap->getTileSize().height / 2, winSize.height / 2); // 同上
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Point actualPosition = ccp(x, y);

	Point centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	Point viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}

void HelloWorld::setPlayerPosition(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position);
	int tileGid = _meta->tileGIDAt(tileCoord); // 得到全局唯一标识（物理属性）
	if (tileGid)
	{
		Value properties = _tileMap->propertiesForGID(tileGid);
		ValueMap map = properties.asValueMap();
		bool isCollidable = map["Collidable"].asBool();
		if (isCollidable)
		{
			return; // 阻挡，不能动
		}
		bool isCollectable = map["Collectable"].asBool();
		if (isCollectable)
		{
			_meta->removeTileAt(tileCoord);
			_foreground->removeTileAt(tileCoord); //道具，清除掉
		}
	}
	_player->setPosition(position);
}

void HelloWorld::ccTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
	return;
}

void HelloWorld::ccTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
	Point touchLocation = touches[0]->getLocationInView();
	touchLocation = Director::sharedDirector()->convertToGL(touchLocation);
	touchLocation = this->convertToNodeSpace(touchLocation);

	Point playerPos = _player->getPosition();
	Point diff = ccpSub(touchLocation, playerPos);

	if (abs(diff.x) > abs(diff.y))
	{
		if (diff.x > 0)
		{
			playerPos.x += _tileMap->getTileSize().width;
		}
		else
		{
			playerPos.x -= _tileMap->getTileSize().width;
		}
	}
	else
	{
		if (diff.y > 0)
		{
			playerPos.y += _tileMap->getTileSize().height;
		}
		else
		{
			playerPos.y -= _tileMap->getTileSize().height;
		}
	}

	// safety check on the bounds of the map
	if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
		playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
		playerPos.y >= 0 && playerPos.x >= 0)
	{
		this->setPlayerPosition(playerPos);
	}

	this->setViewPointCenter(_player->getPosition());
}

Point HelloWorld::tileCoordForPosition(Point position)
{
	// 地图坐标与界面坐标转换
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;

	return ccp(x, y);
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	Director::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
