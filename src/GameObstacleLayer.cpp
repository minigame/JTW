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

	//create elevator
	m_elevatorSprite_upAndDown = ElevatorSprite::create();
	m_elevatorSprite_upAndDown->setOriginPosition(Point(200.0f, 400.0f));
	m_elevatorSprite_upAndDown->setReturnLength(100.0f);
	m_elevatorSprite_upAndDown->setSpeed(50.0f);
	m_elevatorSprite_upAndDown->setDirection(UpAndDown);
	this->addChild(m_elevatorSprite_upAndDown);

	m_elevatorSprite_leftAndRight = ElevatorSprite::create();
	m_elevatorSprite_leftAndRight->setOriginPosition(Point(500.0f, 600.0f));
	m_elevatorSprite_leftAndRight->setReturnLength(80.0f);
	m_elevatorSprite_leftAndRight->setSpeed(80.0f);
	m_elevatorSprite_leftAndRight->setDirection(LeftAndRight);
	this->addChild(m_elevatorSprite_leftAndRight);

	//create bridge
	m_bridgetSprite = BridgeSprite::create();
	this->addChild(m_bridgetSprite);
	m_bridgetSprite->setPosition(Vec2(1000.0f, 380));

	return true;
}