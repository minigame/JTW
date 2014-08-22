#ifndef ElevatorSprite_h__
#define ElevatorSprite_h__

#include "cocos2d.h"
#include "ResourceMgr.h"
#include "cocostudio/CocoStudio.h"
#include "PhyConst.h"

class ElevatorSprite :
	public cocos2d::Sprite
{
public:
	ElevatorSprite();
	~ElevatorSprite();

	virtual bool init();
	CREATE_FUNC(ElevatorSprite);
	void update(float dt);

private:
	cocos2d::PhysicsBody* m_phyBox;
	float m_speed;
	cocos2d::Vec2 m_originPosition;
	float m_returnLength;
};
#endif
