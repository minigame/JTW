#ifndef __GateSprite__H
#define __GateSprite__H

#include "cocos2d.h"
#include "ResourceMgr.h"
#include "PhyConst.h"
#include "Tag.h"

enum ZHOUDIR {Down, Top};
enum GateStatus {Line, Rotate};

#define MoveRange 100

class GateSprite: public cocos2d::Sprite
{
public:
	GateSprite();
	~GateSprite();
    bool init();
    CREATE_FUNC(GateSprite);



public:
	cocos2d::PhysicsBody* m_phyBox;
	Sprite* m_gate;
	Sprite* m_zhou;
	void setPhyBox();
	ZHOUDIR m_dir;
	GateStatus m_status;
	void setZhouDir(ZHOUDIR dir);
	void setGateRunStatus(GateStatus s);
};

#endif
