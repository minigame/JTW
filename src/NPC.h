#ifndef _NPC_H_
#define _NPC_H_
/*!
 * \file NPC.h
 * \date 2014/08/10 20:29
 *
 * \author leozzyzheng   lunchunliu   jiaxinli
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 所有非玩家生物
 *
 * \note
*/
#include "Creature.h"
class NPC :
	public Creature
{
public:
	NPC();
	~NPC();
};

#endif

