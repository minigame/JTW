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
 * TODO: ����� 
 *
 * \note
*/
#include "Creature.h"
#include "cocos2d.h"
#include "Log.h"
#include "CommonMarco.h"
#include "CallBackMgr.h"
#include "Tag.h"

using namespace cocos2d;

class Player : public Creature
{
public:
	Player();
	~Player();

//���캯��
public:
	void init();

//��Ա����
public:
	void changeAnotherRole();

protected:
	virtual void onAttackEnd(cocostudio::Armature * armatrue, cocostudio::MovementEventType type, const std::string& id);
	virtual void onFrameEvent(cocostudio::Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex);
	virtual void deadCompleted();
	virtual int  getMaxAttackCount() const;
	virtual void onAttacked();
	virtual void onUpdateDir();
	virtual void onRoleChanged();
	

private:
	void creatPigAttackRegion();
	void removePigAttackRegion();

	//����Pig�Ľ���������
	cocos2d::PhysicsShapeBox* m_pigAttackRegion;
};

#endif
