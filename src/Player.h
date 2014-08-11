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

enum ROLE {Monkey, Pig, Puffer};   //猴子，猪，河豚

class Player :
	public Creature
{
public:
	Player();
	~Player();

//构造函数
public:
	Player(ROLE r);

//成员变量
public:
	ROLE m_eCurrentRole;    //当前player的角色
	void init();


//成员函数
public:
	void setRole(ROLE r);
	void changeRole(ROLE r);
};

#endif

