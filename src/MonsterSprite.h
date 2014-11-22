#ifndef MonsterSprite_h__
#define MonsterSprite_h__

/*!
 * \file MonsterOneSprite.h
 * \date 2014/08/28 9:56
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: monster怪物
 *
 * \note
*/
#include "NPCSprite.h"
class MonsterOneSprite :
	public NPCSprite
{
public:
	MonsterOneSprite();
	~MonsterOneSprite();

	virtual bool init();
	CREATE_FUNC(MonsterOneSprite);

	virtual void AI(Point playerPos);
};

class MonsterTwoSprite :
	public NPCSprite
{
public:
	MonsterTwoSprite();
	~MonsterTwoSprite();

	virtual bool init();
	CREATE_FUNC(MonsterTwoSprite);

	virtual void AI(Point playerPos);
};

#endif // MonsterSprite_h__

