
#ifndef GameObstacleLayer_h__
#define GameObstacleLayer_h__

#include "cocos2d.h"
#include "Log.h"
#include "ElevatorSprite.h"

using namespace cocos2d;

class GameObstacleLayer : public cocos2d::Layer
{
public:
	GameObstacleLayer();
	~GameObstacleLayer();
	virtual bool init();
	CREATE_FUNC(GameObstacleLayer);

private:
	ElevatorSprite* m_elevatorSprite;
};
#endif
