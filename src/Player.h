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
#include "DataConversion.h"
#include "ResourceMgr.h"
#include "CommonMarco.h"
#include "CallBackMgr.h"

using namespace cocos2d;

#define A2B 4

class Player : public Creature
{
public:
	Player();
	~Player();

//���캯��
public:
	Player(ROLE r);
	void init();

//��Ա����
private:
	ROLE m_currentRole;    //��ǰplayer�Ľ�ɫ
	//ʹ��vec���洢״̬ö�٣����Խ�����״̬���ӽ��룬����ÿ��״ֻ̬����һ��
	std::vector<STATUS> m_currentStatus;
	float f_verticalSpeed;   //����ٶ��Ǵ��ⲿ�ļ������   ��ֱ���ٶ�
	float f_horizontalSpeed;   //����ٶ��Ǵ��ⲿ�ļ������   ˮƽ�ٶ�
	//����Pig�Ľ���������
	cocos2d::PhysicsShapeBox* m_pigAttackRegion;

	int m_currentBlood;   //��ǰѪ��
	int m_maxBlood;       //����Ѫ��
	int m_beAttackedNum;    //�յ������Ĵ���


//��Ա����
public:
	ROLE getRole();
	//STATUS getStatus();
	void changeRole(ROLE r);
	void changeAnotherRole();
	//void setStatus(STATUS s);
	//�ı�״̬�������bool��־�Ǽ�����������true������룬����ɾ��
	void changeStatus(STATUS s, bool isSet);
	//void setRoleAndStatus(ROLE r, STATUS s);
	void onCollisionHandle(Vec2 normal);
	//���㵱ǰ����������STATUS����������������;
	STATUS calculateStatuesForAnimation();

	void setBlood(int b);  //����Ѫ��
	int getBlood();  //�õ���ǰ��Ѫ��
	void setBeAttackedNum(int num);   //���ñ������Ĵ���
	int getBeAttackedNum();    //�õ���ǰ�Ѿ����������ٴ�
	void addbeAttackedNum();    //�ܹ����Ĵ�����1
	void addbeAttackedNum(int addnum);    //�ܹ����Ĵ�����addnum
	

private:
	void updateSpeed(STATUS s, bool isCancel, bool isFind);
	void updateAnimatonPlayStatus(STATUS s);
	void getAnimationNameByRole(std::string& name);
	//���ص��Ǽ�������ĵ�ǰ����Ӧ���е�״̬
	STATUS getAnimationNameByRoleAndStatus(std::string& name);
	void updateArmatureAndPhyBodyByRoleAndStatus();
	void setRole(ROLE r);
	void updateBitMask();
	//Ѱ��״̬������ҵ������±꣬���Ƕ���NoAction���ص�ʱ��vectorΪ�գ�����ʹ���±�
	int  findStatus(STATUS s);
	void printStatus();
	void updateDir(STATUS s, bool isCancel);
	void onAttackEnd(cocostudio::Armature * armatrue, cocostudio::MovementEventType type, const std::string& id);
	//����֮���������������ɵ�״̬
	void clearLikeFlyStatus();
	//�Ƴ�PIG��������
	void removePigAttackRegion(float);
	//����PIG��������
	void creatPigAttackRegion(cocostudio::Armature * armatrue);
	//�������˵Ĵ���������Ѫ��
	void updateBlood();   
};

#endif
