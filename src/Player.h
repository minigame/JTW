#ifndef _PLAYER_H_
#define _PLAYER_H_
/*!
 * \file Player.h
 * \date 2014/08/10 20:31
 *
 * \author leozzyzheng   lunchunliu    jiaxinli
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


using namespace cocos2d;

#define WALK_TAG "run"
#define JUMP_TAG "jump"
#define DIE_TAG  "die"
#define MONKEY_TAG "monkey"
#define PIG_TAG "pig"
#define PUFFER_TAG	"puffer"

enum ROLE {Monkey, Pig, Puffer};   //猴子，猪，河豚
enum STATUS {NoAnyAction, Walk, Jump, Die};    //没有任何动作状态，走的状态，跳跃的状态，死亡的状态

class Player : public Creature
{
public:
	Player();
	~Player();

//构造函数
public:
	Player(ROLE r);

//成员变量
public:
	ROLE m_currentRole;    //当前player的角色
	STATUS m_currentStatus;   //当前的状态
	void init();


//成员函数
public:
	ROLE getRole();
	STATUS getStatus();
	void setRole(ROLE r);
	void changeRole(ROLE r);
	void getAnimationNameByRole(std::string& name);
	void getAnimationNameByRoleAndStatus(std::string& name);
	void setStatus(STATUS s);
	void changeStatus(STATUS s);

private:
	void updateAnimatonPlayStatus();
};

#endif

