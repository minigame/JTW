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
	void setSpeed(Vec2 v);    //���ø�����������ٶ�
	Vec2 getSpeed() const;
	cocostudio::Armature * getArmature() const;
	void bindPhyBody(Node* parent);    //��armature��body
	void setMaxBlood(int blood);
	int  getMaxBlood() const;
	void setBlood(int b); //����Ѫ��;
	int  getBlood() const; //�õ���ǰ��Ѫ��;
	void setBeAttackedNum(int num); //���ñ������Ĵ���;
	int  getBeAttackedNum() const; //�õ���ǰ�Ѿ����������ٴ�;
	void addbeAttackedNum(int addnum); //�ܹ����Ĵ�����addnum;
	void addbeAttackedNum(); //�ܹ����Ĵ�����1;
	void update(float dt);
	void walk(bool isForward, bool isCancel);
	void attack(bool isCancel);
	void jump(bool isCancel);
	std::string getStatusTag(STATUS s);
	void changeRole(ROLE r);
	ROLE getRole() const;
	void onCollisionHandle(Vec2 normal);
	void changeDir(DIR r);
	void onCollisionEnd(Vec2 normal);

protected:
	void updateAnimation(STATUS s);
	void updateAnimatonPlayStatus(STATUS s);
	void clearFly();
	virtual void onAttackEnd(cocostudio::Armature * armatrue, cocostudio::MovementEventType type, const std::string& id);
	cocos2d::PhysicsBody* getPhyBody() const;

private:
	void setDir(DIR d);    //���ø���������߷���
	void setRole(ROLE r);
	void updateBlood(); //�������˵Ĵ���������Ѫ��;
	bool setArmatureWithAnimationName(const char* name);   //��ArmatureDataManagerChe����ͨ���������֣���Armature��ֵ
	void setPhyByArmatureContentSize(bool fourceChange);       //����Armature����̬����bodybox�Ĵ�С
	void updateRoleName();
	void setWalkSpeed(bool isRight, bool isRemove, bool isChangeStatus = true);
	void resumeSpeed();
	void innerInit();
	bool checkWalkable();

	unsigned int m_status;

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
};

#endif
