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
	this->addChild(m_elevatorSprite);

	return true;
}