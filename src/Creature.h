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
 * TODO: ��������Ļ���
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

//���캯��
public:
	Creature(float currentBlood, float maxBlood, DIR d);

//��Ա����
public:
	virtual void init(ROLE r, STATUS s = NoAnyAction);    //��ʼ������������ľ���ͼƬ�򶯻�������д����
	DIR  getDir() const;
	Vec2 getSpeed() const;
	cocostudio::Armature * getArmature() const;
	void bindPhyBody(Node* parent);    //��armature��body
	void setMaxBlood(int blood);
	int  getMaxBlood() const;
	void setBlood(int b); //����Ѫ��;
	int  getBlood() const; //�õ���ǰ��Ѫ��;
	int  getBeAttackedNum() const; //�õ���ǰ�Ѿ����������ٴ�;
	void addbeAttackedNum(int attackDirection, int num = 1); //�ܹ����Ĵ�����1 ���Զ���;
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
	//����Ҫ���ø���ĺ���
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
	void setDir(DIR d);    //���ø���������߷���
	void updateBlood(); //�������˵Ĵ���������Ѫ��;
	bool setArmatureWithAnimationName(const char* name);   //��ArmatureDataManagerChe����ͨ���������֣���Armature��ֵ
	void setPhyByArmatureContentSize(bool fourceChange);       //����Armature����̬����bodybox�Ĵ�С
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

	int m_currentBlood;   //��ǰѪ��
	int m_maxBlood;       //����Ѫ��
	int m_beAttackedNum;  //�յ������Ĵ���

	cocostudio::Armature* m_armature;    //�������armature
	cocos2d::PhysicsBody* m_phyBox;
	DIR m_dir;    //��Creature�ķ���

	float m_verticalSpeed;   //����ٶ��Ǵ��ⲿ�ļ������   ��ֱ���ٶ�
	float m_horizontalSpeed;   //����ٶ��Ǵ��ⲿ�ļ������   ˮƽ�ٶ�

	ROLE m_currentRole;    //��ǰ�Ľ�ɫ
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
