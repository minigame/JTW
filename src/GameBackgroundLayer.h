//  GameBackgroundLayer.h
//  JTW
//
//  Created by alexzzp on 14-8-13.
//	Modified by leozzyzheng on 14-8-15
//


#ifndef GameBackgroundLayer_h__
#define GameBackgroundLayer_h__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

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
	Point tileCoordForPosition(Point position);
	void setPhyWorld(PhysicsWorld* world);
	TMXTiledMap* getTiledMap() const;
private:
	TMXTiledMap* m_tileMap;
	TMXLayer* m_meta;
	TMXLayer* m_foreground;
	TMXLayer* m_background;
	Sprite * m_physicLayer;
	Point m_lastPosition;
	bool m_isMapMove;
	PhysicsWorld* m_world;
};

#endif // GameBackgroundLayer_h__
