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

using namespace cocos2d;
using namespace std;

enum GearDirection { GEAR_UP, GEAR_DOWN, GEAR_LEFT, GEAR_RIGHT, GEAR_STATIC };

typedef struct GearAttribute
{
	Point coord;
	Point position;
	enum GearDirection direction;
	int period;
	int stop;
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
	void readGearAttributes();
	void buildMapByPhyBoxes();
	void createPhyBox(Point position, Size size);
	Point tileCoordForPosition(Point position);
	Point positionForTileCoord(Point tileCoord);

private:
	struct GearAttribute * m_gears;
	int m_gearCount;
	TMXTiledMap* m_tileMap;
	//TMXLayer* m_foreground;
	TMXObjectGroup* m_physics;
	TMXObjectGroup* m_gear;
	TMXLayer* m_background;
	//Sprite * m_physicLayer;
	Point m_lastPosition;
	bool m_isMapMove;
	PhysicsWorld* m_world;
};

#endif // GameBackgroundLayer_h__
