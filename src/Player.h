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
#include "DataConversion.h"
#include "ResourceMgr.h"
#include "CommonMarco.h"
#include "CallBackMgr.h"

using namespace cocos2d;

#define A2B 4

class Player : public Creature
{
public:
	Player();
	~Player();

//构造函数
public:
	Player(ROLE r);
	void init();

//成员变量
private:
	ROLE m_currentRole;    //当前player的角色
	//使用vec来存储状态枚举，可以将多种状态叠加进入，但是每种状态只能有一个
	std::vector<STATUS> m_currentStatus;
	float f_verticalSpeed;   //这个速度是从外部文件读入的   垂直的速度
	float f_horizontalSpeed;   //这个速度是从外部文件读入的   水平速度
	//保存Pig的近身攻击区域
	cocos2d::PhysicsShapeBox* m_pigAttackRegion;

	int m_currentBlood;   //当前血量
	int m_maxBlood;       //最大的血量
	int m_beAttackedNum;    //收到攻击的次数


//成员函数
public:
	ROLE getRole();
	//STATUS getStatus();
	void changeRole(ROLE r);
	void changeAnotherRole();
	//void setStatus(STATUS s);
	//改变状态，后面的bool标志是加入与否，如果是true，则加入，否则删除
	void changeStatus(STATUS s, bool isSet);
	//void setRoleAndStatus(ROLE r, STATUS s);
	void onCollisionHandle(Vec2 normal);
	//计算当前决定动画的STATUS，切勿用于其他用途
	STATUS calculateStatuesForAnimation();

	void setBlood(int b);  //设置血量
	int getBlood();  //得到当前的血量
	void setBeAttackedNum(int num);   //设置被攻击的次数
	int getBeAttackedNum();    //得到当前已经被攻击多少次
	void addbeAttackedNum();    //受攻击的次数加1
	void addbeAttackedNum(int addnum);    //受攻击的次数加addnum
	

private:
	void updateSpeed(STATUS s, bool isCancel, bool isFind);
	void updateAnimatonPlayStatus(STATUS s);
	void getAnimationNameByRole(std::string& name);
	//返回的是计算出来的当前动画应该有的状态
	STATUS getAnimationNameByRoleAndStatus(std::string& name);
	void updateArmatureAndPhyBodyByRoleAndStatus();
	void setRole(ROLE r);
	void updateBitMask();
	//寻找状态，如果找到返回下标，但是对于NoAction返回的时候vector为空，切勿使用下标
	int  findStatus(STATUS s);
	void printStatus();
	void updateDir(STATUS s, bool isCancel);
	void onAttackEnd(cocostudio::Armature * armatrue, cocostudio::MovementEventType type, const std::string& id);
	//调用之后消除类似跳，飞的状态
	void clearLikeFlyStatus();
	//移除PIG攻击区域
	void removePigAttackRegion(float);
	//生成PIG攻击区域
	void creatPigAttackRegion(cocostudio::Armature * armatrue);
	//根据受伤的次数，更新血量
	void updateBlood();   
};

#endif
