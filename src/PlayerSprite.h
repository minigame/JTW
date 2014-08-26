#ifndef PlayerSprite_h__
#define PlayerSprite_h__

/*!
 * \file PlayerSprite.h
 * \date 2014/08/15 17:45
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#include "cocos2d.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "Tag.h"
#include "CallBackMgr.h"
#include "ElevatorSprite.h"

class PlayerSprite : public cocos2d::Sprite
{
public:
	PlayerSprite();
	~PlayerSprite();

	virtual bool init();
	void walk(bool isForward, bool isCancel);
	void jump(bool isCancel);
	void attack(bool isCancel);
	void onCollisionHandle(Vec2 normal);
	void onCollisionEnd(Vec2 normal);
	void setNormal(Vec2 normal);
	void updateDirection(CallBackData * data);
	void changeRole(ROLE role);
	ROLE getRole();
	CREATE_FUNC(PlayerSprite);
	//void updateBloodUI();   //这个更新血量UI
	void beAttacked();    //受1次攻击
	void beAttacked(int addnum);    //受addnum次攻击
	Player* getPlayer();
	void createBullet(CallBackData * data);
	void onContactWithElevator(ElevatorSprite* elevator);
	void SeperateWithElevator();
	void update(float dt);

private:
	Player * m_player;
	Vec2 m_normal;

	//与电梯一起移动需要的参数
	float m_speedContactWithElevator;
	Direction m_directionContactWithElevator;
	ElevatorSprite * m_elevator;
};
#endif // PlayerSprite_h__

