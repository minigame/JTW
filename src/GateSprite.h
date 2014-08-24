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


	//成员变量
public:
	cocos2d::PhysicsBody* m_phyBox;
	Sprite* m_gate;
	Sprite* m_zhou;
	ZHOUDIR m_dir;
	GateStatus m_status;
	int m_totalMove;
	int m_detaMove;
	int m_MoveDir;   //0是向左，1是向右


	//成员函数
public:
	void setPhyBox();
	void setZhouDir(ZHOUDIR dir);
	void setGateRunStatus(GateStatus s);
	void startRun();
	void runLine();
	void runRotate();


	

private:
	void run(float dt);
};

#endif
