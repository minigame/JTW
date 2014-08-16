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
 * TODO: ����� 
 *
 * \note
*/
#include "Creature.h"
#include "cocos2d.h"


using namespace cocos2d;

enum ROLE {Monkey, Pig, Puffer};   //���ӣ�������
enum STATUS {NoAnyAction, Walk, Jump, Die};    //û���κζ���״̬���ߵ�״̬����Ծ��״̬��������״̬

class Player : public Creature
{
public:
	Player();
	~Player();

//���캯��
public:
	Player(ROLE r);

//��Ա����
public:
	ROLE m_currentRole;    //��ǰplayer�Ľ�ɫ
	STATUS m_currentStatus;   //��ǰ��״̬
	void init();


//��Ա����
public:
	ROLE getRole();
	STATUS getStatus();
	void setRole(ROLE r);
	void changeRole(ROLE r);
	void getAnimationNameByRole(std::string& name);
	void getAnimationNameByRoleAndStatus(std::string& name);
	void setStatus(STATUS s);
	void changeStatus(STATUS s);
};

#endif

