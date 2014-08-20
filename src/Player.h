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

using namespace cocos2d;

#define WALK_TAG "run"
#define JUMP_TAG "jump"
#define DIE_TAG  "die"
#define NOANYACTION_TAG "noaction"
#define FLY_TAG "noaction"
#define ATTACK_TAG "fight"
#define MONKEY_TAG "monkey"
#define PIG_TAG "pig"
#define PUFFER_TAG	"puffer"

enum ROLE {Monkey, Pig, Puffer};   //猴子，猪，河豚
enum STATUS {NoAnyAction, LeftWalk, RightWalk, Jump, Die, Attack, Fly};    //没有任何动作状态，走的状态，跳跃的状态，死亡的状态

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
	//保存当前player的攻击区域
	cocos2d::Rect m_attackRegion;
	

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
};

#endif
