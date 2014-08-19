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
#include "Log.h"

using namespace cocos2d;

#define WALK_TAG "run"
#define JUMP_TAG "jump"
#define DIE_TAG  "die"
#define NOANYACTION_TAG "noaction"
#define MONKEY_TAG "monkey"
#define PIG_TAG "pig"
#define PUFFER_TAG	"puffer"

enum ROLE {Monkey, Pig, Puffer};   //���ӣ�������
enum STATUS {NoAnyAction, LeftWalk, RightWalk, Jump, Die};    //û���κζ���״̬���ߵ�״̬����Ծ��״̬��������״̬

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

//��Ա����
public:
	ROLE getRole();
	//STATUS getStatus();
	void changeRole(ROLE r);
	//void setStatus(STATUS s);
	//�ı�״̬�������bool��־�Ǽ�����������true������룬����ɾ��
	void changeStatus(STATUS s, bool isSet);
	//void setRoleAndStatus(ROLE r, STATUS s);
	void onCollisionHandle(Vec2 normal);
	//���㵱ǰ����������STATUS����������������;
	STATUS calculateStatuesForAnimation();

private:
	void updateSpeed(STATUS s, bool isCancel, bool isFind);
	void updateAnimatonPlayStatus(STATUS s);
	void getAnimationNameByRole(std::string& name);
	//���ص��Ǽ�������ĵ�ǰ����Ӧ���е�״̬
	STATUS getAnimationNameByRoleAndStatus(std::string& name);
	void updateArmatureAndPhyBodyByRoleAndStatus();
	void setRole(ROLE r);
	void updateBitMask();
	bool findStatus(STATUS s);
	void printStatus();
	void updateDir(STATUS s, bool isCancel);
};

#endif
