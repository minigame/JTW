#ifndef CallBackData_h__
#define CallBackData_h__

#include "CommonMarco.h"

class NPCSprite;

class CallBackData
{
public:
	CallBackData(void);
	~CallBackData(void);

	virtual void nothing(){}
};

class CreatureDirData : public CallBackData
{
public:
	DIR dir;
};

class RemoveMonsterData : public CallBackData
{
public:
	NPCSprite * toBeRemoved;
};

class CreatureHpData : public CallBackData
{
public:
	int hp;
};

#endif // CallBackData_h


