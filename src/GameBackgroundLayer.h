//  GameBackgroundLayer.h
//  JTW
//
//  Created by alexzzp on 14-8-13.
//	Modified by leozzyzheng on 14-8-15
//


#ifndef GameBackgroundLayer_h__
#define GameBackgroundLayer_h__

#include "cocos2d.h"
#include "Log.h"
#include "DataConversion.h"
#include "GameObstacleLayer.h"

using namespace cocos2d;
using namespace std;

enum GearDirection { GEAR_UP, GEAR_DOWN, GEAR_LEFT, GEAR_RIGHT, GEAR_STATIC };
enum GearType { GEAR_BRIDGE, GEAR_LIFT, GEAR_DOOR, GEAR_BOOM, GEAR_STONE, GEAR_HURT, GEAR_OBJECT };

struct GearAttribute
{
	GearType type;
	Point position;
	Point coord;
	Size size;
	GearDirection direction;
	GearDirection direction_self;
	int speed;
	int period;
	int count;
	int distance;
	int offset;
};

class GameBackgroundLayer: public Layer
{
public:
	GameBackgroundLayer(void);
    
	~GameBackgroundLayer(void);
    
	virtual bool init();
	void setViewPointCenter(Point position);
	void updatePhysic(Point position);
	void setMapMoveEnable(bool enable);
	bool getMapMoveEnable() const;
	CREATE_FUNC(GameBackgroundLayer);
	void setPhyWorld(PhysicsWorld* world);
	TMXTiledMap* getTiledMap() const;
	bool setTiledMap(TMXTiledMap* tiledMap);
	bool setTiledMap(string path);
	void setObstacleLayer(GameObstacleLayer* layer);
	void readGearAttributes();
	void buildPlayers();
	void buildGears();
	void buildMapByPhyBoxes();
	void createPhyBox(Point position, Size size);
	Point tileCoordForPosition(Point position);
	Point positionForTileCoord(Point tileCoord);
	int checkCoins(Point pos, Size size);

private:
	GearAttribute * m_gears;
	int m_gearCount;
	TMXTiledMap* m_tileMap;
	//TMXLayer* m_foreground;
	TMXObjectGroup* m_physics;
	TMXObjectGroup* m_gear;
	TMXObjectGroup* m_player;
	TMXLayer* m_background;
	TMXLayer* m_coin;
	//Sprite * m_physicLayer;
	Point m_lastPosition;
	bool m_isMapMove;
	PhysicsWorld* m_world;
	GameObstacleLayer* m_obstacleLayer;
};

#endif // GameBackgroundLayer_h__
