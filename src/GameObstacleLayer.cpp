#include "GameObstacleLayer.h"

GameObstacleLayer::GameObstacleLayer()
{
	m_elevatorSprite_leftAndRight = NULL;
	m_elevatorSprite_upAndDown = NULL;
}


GameObstacleLayer::~GameObstacleLayer()
{
}

bool GameObstacleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_forts.clear();

	//create elevator
	/*m_elevatorSprite_upAndDown = ElevatorSprite::create();
	m_elevatorSprite_upAndDown->setOriginPosition(Point(200.0f, 400.0f));
	m_elevatorSprite_upAndDown->setReturnLength(100.0f);
	m_elevatorSprite_upAndDown->setSpeed(50.0f);
	m_elevatorSprite_upAndDown->setDirection(UpAndDown);
	m_elevatorSprite_upAndDown->setTag(ELEVATOR_TAG);
	this->addChild(m_elevatorSprite_upAndDown);

	m_elevatorSprite_leftAndRight = ElevatorSprite::create();
	m_elevatorSprite_leftAndRight->setOriginPosition(Point(500.0f, 600.0f));
	m_elevatorSprite_leftAndRight->setReturnLength(80.0f);
	m_elevatorSprite_leftAndRight->setSpeed(80.0f);
	m_elevatorSprite_leftAndRight->setDirection(LeftAndRight);
	m_elevatorSprite_leftAndRight->setTag(ELEVATOR_TAG);
	this->addChild(m_elevatorSprite_leftAndRight);*/
    
    // create fort
    // 建立炮台
    /*FortSprite * fort = FortSprite::create();
    fort->setDir(FortSpriteDirection::right);
    fort->setPosition(Vec2(100.0f, 200.0f));
    this->addChild(fort);
    fort->shootOnTimer(1, 100, 1000);*/ // int interval, int repeatCount, int speed
    //fort->shoot(600);

	// 建立石头做实�?
	/*auto stone = StoneSprite::create();
	stone->setPosition(Vec2(150.0f, 150.0f));
	this->addChild(stone);*/

	//create bridge
	/*m_bridgetSprite = BridgeSprite::create();
	this->addChild(m_bridgetSprite);
	m_bridgetSprite->setPosition(Vec2(1000.0f, 380));*/

	return true;
}

void GameObstacleLayer::updateGears( Point playerPos )
{
	std::vector<FortSprite*>::const_iterator it = m_forts.cbegin();

	for(; it != m_forts.cend(); ++it)
	{
		FortSprite * fort = *it;
		fort->AI(playerPos);
	}
}

void GameObstacleLayer::addFort( FortSprite * sprite )
{
	m_forts.push_back(sprite);
	addChild(sprite);
}
