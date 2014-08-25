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

private:
	unsigned int m_status;

	void updateRoleName();
	void onAttackEnd(cocostudio::Armature * armatrue, cocostudio::MovementEventType type, const std::string& id);
	void setWalkSpeed(bool isRight, bool isRemove, bool isChangeStatus = true);
	void resumeSpeed();
	void innerInit();
	bool checkWalkable();

public:
	void update(float dt);
	void walk(bool isForward, bool isCancel);
	void attack(bool isCancel);
	void jump(bool isCancel);
	std::string getStatusTag(STATUS s);
	void setRole(ROLE r);
	void changeRole(ROLE r);
	ROLE getRole() const;
	void onCollisionHandle(Vec2 normal);
	void changeDir(DIR r);
	void onCollisionEnd(Vec2 normal);

//成员变量
protected:
	void updateAnimation(STATUS s);
	void updateAnimatonPlayStatus(STATUS s);
	void clearFly();
	void setDir(DIR d);    //设置该生物的行走方向

	Vec2 m_position;     //改生物的位置，这个位置是相对于卷轴的,且是中心位置    ??????????????????
	float m_currentBlood;     //血量
	float m_maxBlood;        //该生物最大血量值
	cocostudio::Armature* m_armature;    //该生物的armature
	cocos2d::PhysicsBody* m_phyBox;
	DIR m_dir;    //该Creature的方向

	float m_verticalSpeed;   //这个速度是从外部文件读入的   垂直的速度
	float m_horizontalSpeed;   //这个速度是从外部文件读入的   水平速度

	ROLE m_currentRole;    //当前的角色
	std::string m_currentRoleName;

	float m_lastHorSpeed;
	STATUS lastPressedDirectionBtn;

//构造函数
public:
	Creature(float currentBlood, float maxBlood, DIR d);

//成员函数
public:
	virtual void init();    //初始化函数，生物的精灵图片或动画的生成写在这
	void setArmature(cocostudio::Armature* armature);    //设置该生物的armature
	//void setPhyBody(cocos2d::PhysicsBody* bodyBox);     //设置该生物的物理属性body这个成语变量，不代表该armature和body绑定
	void setTag(int tag);   //给m_armature设置tag
	bool setArmatureWithAnimationName(const char* name);   //从ArmatureDataManagerChe里面通过动画名字，给Armature赋值
	void setArmatureWithExportJsonFile(char* filename, char* armatureName);    //通过ExportJson的文件名和动画名字创建Armature给m_armature
	void setAnimationDirByDIR();      //通过该生物的DIR设置动画播放的方向，向右走是正常播放，向左走是反向播放
	DIR  getDir() const;
	void setSpeed(Vec2 v);    //设置该生物的物理速度
	Vec2 getSpeed();
	cocostudio::Armature * getArmature() const;
	void bindPhyBody(Node* parent);    //绑定armature和body
private:
	
	void setPhyByArmatureContentSize(bool fourceChange);       //根据Armature的形态设置bodybox的大小
};

#endif
