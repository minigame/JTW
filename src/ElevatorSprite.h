#ifndef ElevatorSprite_h__
#define ElevatorSprite_h__

#include "cocos2d.h"
#include "ResourceMgr.h"
#include "cocostudio/CocoStudio.h"
#include "PhyConst.h"
#include "Tag.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

enum Direction { UpAndDown, LeftAndRight };

class ElevatorSprite :
	public cocos2d::Sprite
{
public:
	ElevatorSprite();
	~ElevatorSprite();

	virtual bool init();
	CREATE_FUNC(ElevatorSprite);
	void update(float dt);
	void setOriginPosition(Vec2 point);
	Vec2 getOriginPosition();
	void setReturnLength(float length);
	float getReturnLength();
	void setSpeed(float speed);
	float getSpeed();
	void setDirection(Direction direction);
	Direction getDirection();

private:
	cocos2d::PhysicsBody* m_phyBox;
	float m_speed;
	cocos2d::Vec2 m_originPosition;
	float m_returnLength;
	Direction m_direction;
};
#endif
