#ifndef _CREATURE_H_
#define _CREATURE_H_

/*!
 * \file Creature.h
 * \date 2014/08/10 20:30
 *
 * \author leozzyzheng  lunchunliu  jiaxinli
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 所有生物的基类
 *
 * \note
*/

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "EventDef.h"
#include "CommonMarco.h"
#include "PhyConst.h"
#include "DataConversion.h"
#include "ResourceMgr.h"
#include "Log.h"
#include "CallBackMgr.h"
#include "BulletSprite.h"

using namespace cocos2d;

class Creature 
{
public:
	Creature();
	~Creature();

//构造函数
public:
	Creature(float currentBlood, float maxBlood, DIR d);

//成员函数
public:
	virtual void init(ROLE r, STATUS s = NoAnyAction);    //初始化函数，生物的精灵图片或动画的生成写在这
	DIR  getDir() const;
	Vec2 getSpeed() const;
	cocostudio::Armature * getArmature() const;
	void bindPhyBody(Node* parent);    //绑定armature和body
	void setMaxBlood(int blood);
	int  getMaxBlood() const;
	void setBlood(int b); //设置血量;
	int  getBlood() const; //得到当前的血量;
	int  getBeAttackedNum() const; //得到当前已经被攻击多少次;
	void addbeAttackedNum(int attackDirection, int num = 1); //受攻击的次数加1 或自定义;
	void update(float dt);
	void walk(bool isForward, bool isCancel);
	void attack(bool isCancel);
	void jump(bool isCancel);
	virtual std::string getStatusTag(STATUS s);
	void changeRole(ROLE r);
	ROLE getRole() const;
	void onCollisionHandle(Vec2 normal);
	void changeDir(DIR r);
	void onCollisionEnd(Vec2 normal);
	void dead();

protected:
	void updateAnimation(STATUS s);
	void updateAnimatonPlayStatus(STATUS s);
	void clearFly();
	virtual void onAttackEnd(cocostudio::Armature * armatrue, cocostudio::MovementEventType type, const std::string& id);
	virtual void onFrameEvent(cocostudio::Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex);
	cocos2d::PhysicsBody* getPhyBody() const;
	virtual void deadCompleted() = 0;
	void beginAttack();
	//不需要调用父类的函数
	virtual int  getMaxAttackCount() const;
	void beginMarkContinueAttack();
	void EndMarkContinueAttack();
	void dealNextAttack();
	virtual void onAttacked() = 0;
	virtual void onUpdateDir() = 0;

	struct HpData
	{
		int currentBlood;
		int maxBlood;
		int beAttackedNum;
	};

private:
	void setRole(ROLE r);
	void setDir(DIR d);    //设置该生物的行走方向
	void updateBlood(); //根据受伤的次数，更新血量;
	bool setArmatureWithAnimationName(const char* name);   //从ArmatureDataManagerChe里面通过动画名字，给Armature赋值
	void setPhyByArmatureContentSize(bool fourceChange);       //根据Armature的形态设置bodybox的大小
	void updateRoleName();
	void setWalkSpeed(bool isRight, bool isRemove, bool isChangeStatus = true);
	void resumeSpeed();
	void innerInit();
	void resetRoleData(ROLE r);
	bool checkWalkable();
	void setBitmask();
	void setSpeed(Vec2 speed);
	void setSpeedX(float x);
	void setSpeedY(float y);

	unsigned int m_status;

	std::map<ROLE, HpData> m_hpMap;

	int m_currentBlood;   //当前血量
	int m_maxBlood;       //最大的血量
	int m_beAttackedNum;  //收到攻击的次数

	cocostudio::Armature* m_armature;    //该生物的armature
	cocos2d::PhysicsBody* m_phyBox;
	DIR m_dir;    //该Creature的方向

	float m_verticalSpeed;   //这个速度是从外部文件读入的   垂直的速度
	float m_horizontalSpeed;   //这个速度是从外部文件读入的   水平速度

	ROLE m_currentRole;    //当前的角色
	std::string m_currentRoleName;

	float m_lastHorSpeed;
	STATUS lastPressedDirectionBtn;

	int m_jumpCount;

	int m_categorybitmask;
	int m_contacttestbitmask;
	int m_collisionbitmask;

	int m_attackCount;
	int m_attackMaxCount;

	bool m_markContinueAttackFlag;

	float m_attackBackImpulse_X;
	float m_attackBackImpulse_Y;
};

#endif
