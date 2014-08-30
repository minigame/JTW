#ifndef __GateSprite__H
#define __GateSprite__H

#include "cocos2d.h"
#include "ResourceMgr.h"
#include "PhyConst.h"
#include "Tag.h"
#include "DataConversion.h"

enum ZHOUDIR {Down, Top};
enum GateStatus {Line, Rotate};

#define MoveRange 90
#define PAI 3.14159f

class GateSprite: public cocos2d::Sprite
{
public:
	GateSprite();
	~GateSprite();
    bool init();
    CREATE_FUNC(GateSprite);


	//��Ա����
public:
	cocos2d::PhysicsBody* m_phyBox;
	Sprite* m_gate;
	Sprite* m_zhou;
	ZHOUDIR m_dir;
	GateStatus m_status;
	int m_totalMove;
	int m_detaMove;
	int m_MoveDir;   //0������1������
	int m_MoveRange;
	float m_timePerMove;   //����ʱ���˶�һ��


	//��Ա����
public:
	void setPhyBox();
	void setMoveRange(int len);
	void setDir(int dir);   //0������1������
	void setDetaMove(int deta);   //����ÿ���ƶ��ľ���
	void setZhouDir(ZHOUDIR dir);
	void setTimePerMove(float f);
	void setGateRunStatus(GateStatus s);
	void startRun();
	void runLine();
	void runRotate();
	void setTotalMove(int t);


	

private:
	void run(float dt);
};

#endif
