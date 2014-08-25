#ifndef _PLAYER_H_
#define _PLAYER_H_
/*!
 * \file Player.h
 * \date 2014/08/10 20:31
 *
 * \author leozzyzheng   lunchunliu    jiaxinli  longtaochen
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 玩家类 
 *
 * \note
*/
#include "Creature.h"
#include "cocos2d.h"
#include "Log.h"
#include "CommonMarco.h"
#include "CallBackMgr.h"

using namespace cocos2d;

class Player : public Creature
{
public:
	Player();
	~Player();

//构造函数
public:
	void init();

//成员函数
public:
	void changeAnotherRole();

protected:
	virtual void onAttackEnd(cocostudio::Armature * armatrue, cocostudio::MovementEventType type, const std::string& id);
	

private:
	void creatPigAttackRegion();
	void removePigAttackRegion(float delay);

	//保存Pig的近身攻击区域
	cocos2d::PhysicsShapeBox* m_pigAttackRegion;
};

#endif
