#include "GamePlayerLayer.h"
#include "BulletSprite.h"
#include "StoneSprite.h"
#include "FortSprite.h"
#include "GameScene.h"

GamePlayerLayer::GamePlayerLayer()
{
	m_world = NULL;
	m_obstacleLayer = NULL;
};

GamePlayerLayer::~GamePlayerLayer(){};

bool GamePlayerLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	//get the origin point of the X-Y axis, and the visiable size of the screen
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//create a bird and set the position in the center of the screen
    m_playerSprite = PlayerSprite::create();
    m_playerSprite->setPosition(Point(origin.x + visiableSize.width / 2, origin.y + visiableSize.height * 3 / 5 - 10));
    this->addChild(m_playerSprite);

    // 建立石头做实验
    auto stone = StoneSprite::create();
    auto pos = Vec2(origin.x + visiableSize.width / 2 - 100, origin.y + visiableSize.height * 3 / 5 - 100);
    stone->setPosition(pos);
    stone->getPhyBox()->setDynamic(true);
    this->addChild(stone);

    // 建立炮台
//    FortSprite * fort = FortSprite::create();
//    fort->setDir(FortSpriteDirection::right);
//    auto fortPos = Vec2(origin.x + visiableSize.width / 2, origin.y + visiableSize.height * 3 / 5 - 100);
//    fort->setPosition(fortPos);
//    this->addChild(fort);
//    fort->shootOnTimer(1, 100, 1000);
    //fort->shoot(600);

	this->getScheduler()->scheduleUpdate(this,0,false);
	return true;
}

void GamePlayerLayer::onTouch()
{

}

void GamePlayerLayer::onLeftButton(bool isCancel)
{
	m_playerSprite->walk(false, isCancel);
}

void GamePlayerLayer::onRightButton(bool isCancel)
{
	m_playerSprite->walk(true, isCancel);
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

void GamePlayerLayer::setObstacleLayer(GameObstacleLayer* layer)
{
	m_obstacleLayer = layer;
}

void GamePlayerLayer::setBackRollLayer(Layer** backRollLayer)
{
	m_backRollLayer = backRollLayer;
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


	// 防止玩家超出边界
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Point actualPosition = Vec2(x, y);

	Point centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Point viewPoint = centerOfView - actualPosition;
	Point viewPoint2 = viewPoint;

	this->setPosition(viewPoint);
	m_backLayer->setPosition(viewPoint);
	m_obstacleLayer->setPosition(viewPoint);
	for (int i = 0; i < MAX_BACKROLLLAYER; i++) {
		viewPoint2 = Point(viewPoint2.x / 2, viewPoint2.y / 2);
		m_backRollLayer[i]->setPosition(viewPoint2);
	}

	/*LOGD(("position: " + DataConversion::convertPoint2str(position) + "\n").c_str(), NULL);
	LOGD(("actualPosition: " + DataConversion::convertPoint2str(actualPosition) + "\n").c_str(), NULL);
	LOGD(("viewPoint: " + DataConversion::convertPoint2str(viewPoint) + "\n\n").c_str(), NULL);*/
}

void GamePlayerLayer::onChangeRole( ROLE role )
{
	m_playerSprite->changeRole(role);
}


PlayerSprite* GamePlayerLayer::getPlayerSprite()
{
	return m_playerSprite;
}


