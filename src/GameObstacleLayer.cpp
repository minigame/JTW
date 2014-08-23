#include "GameObstacleLayer.h"


GameObstacleLayer::GameObstacleLayer()
{
	m_elevatorSprite = NULL;
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
	m_elevatorSprite = ElevatorSprite::create();
	m_elevatorSprite->setOriginPosition(Point(200.0f, 400.0f));
	m_elevatorSprite->setReturnLength(100.0f);
	m_elevatorSprite->setSpeed(50.0f);
	this->addChild(m_elevatorSprite);


	m_bridgetSprite = BridgeSprite::create();
	this->addChild(m_bridgetSprite);
	m_bridgetSprite->setPosition(Vec2(1000.0f, 380));

	return true;
}