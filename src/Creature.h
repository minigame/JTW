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

//��Ա����
protected:
	void updateAnimation(STATUS s);
	void updateAnimatonPlayStatus(STATUS s);
	void clearFly();
	void setDir(DIR d);    //���ø���������߷���

	Vec2 m_position;     //�������λ�ã����λ��������ھ����,��������λ��    ??????????????????
	float m_currentBlood;     //Ѫ��
	float m_maxBlood;        //���������Ѫ��ֵ
	cocostudio::Armature* m_armature;    //�������armature
	cocos2d::PhysicsBody* m_phyBox;
	DIR m_dir;    //��Creature�ķ���

	float m_verticalSpeed;   //����ٶ��Ǵ��ⲿ�ļ������   ��ֱ���ٶ�
	float m_horizontalSpeed;   //����ٶ��Ǵ��ⲿ�ļ������   ˮƽ�ٶ�

	ROLE m_currentRole;    //��ǰ�Ľ�ɫ
	std::string m_currentRoleName;

	float m_lastHorSpeed;
	STATUS lastPressedDirectionBtn;

//���캯��
public:
	Creature(float currentBlood, float maxBlood, DIR d);

//��Ա����
public:
	virtual void init();    //��ʼ������������ľ���ͼƬ�򶯻�������д����
	void setArmature(cocostudio::Armature* armature);    //���ø������armature
	//void setPhyBody(cocos2d::PhysicsBody* bodyBox);     //���ø��������������body�������������������armature��body��
	void setTag(int tag);   //��m_armature����tag
	bool setArmatureWithAnimationName(const char* name);   //��ArmatureDataManagerChe����ͨ���������֣���Armature��ֵ
	void setArmatureWithExportJsonFile(char* filename, char* armatureName);    //ͨ��ExportJson���ļ����Ͷ������ִ���Armature��m_armature
	void setAnimationDirByDIR();      //ͨ���������DIR���ö������ŵķ������������������ţ��������Ƿ��򲥷�
	DIR  getDir() const;
	void setSpeed(Vec2 v);    //���ø�����������ٶ�
	Vec2 getSpeed();
	cocostudio::Armature * getArmature() const;
	void bindPhyBody(Node* parent);    //��armature��body
private:
	
	void setPhyByArmatureContentSize(bool fourceChange);       //����Armature����̬����bodybox�Ĵ�С
};

#endif
