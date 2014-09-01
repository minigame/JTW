
#ifndef GameObstacleLayer_h__
#define GameObstacleLayer_h__

#include "cocos2d.h"
#include "Log.h"
#include "ElevatorSprite.h"
#include "BridgeSprite.h"
#include "StoneSprite.h"
#include "FortSprite.h"
#include "GateSprite.h"

using namespace cocos2d;

class GameObstacleLayer : public cocos2d::Layer
{
public:
	GameObstacleLayer();
	~GameObstacleLayer();
	virtual bool init();
	void updateGears(Point playerPos);
	void addFort(FortSprite * sprite);
	CREATE_FUNC(GameObstacleLayer);

private:
	ElevatorSprite* m_elevatorSprite_upAndDown;
	ElevatorSprite* m_elevatorSprite_leftAndRight;
	BridgeSprite * m_bridgetSprite;
	std::vector<FortSprite*> m_forts;
};
#endif
