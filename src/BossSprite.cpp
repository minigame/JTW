#include "BossSprite.h"


BossSprite::BossSprite()
{
}


BossSprite::~BossSprite()
{
}

bool BossSprite::init()
{
	if (!NPCSprite::init())
		return false;

	setRole(Boss);

	return true;
}

void BossSprite::AI(Point playerPos)
{
	NPCSprite::AI(playerPos);

	//实现自己的AI

	Point pos = getPosition();

	float distance = pos.distance(playerPos);

	//怪物比玩家的x坐标大表示怪物在右边
	if (pos.x > playerPos.x)
	{
		if (distance <= MONSTER_AI_SHOOT_DISTANCE)
		{
			m_npc->walk(false, true);
			m_npc->walk(false, false);
		}
		
		m_npc->changeDir(Left);
		setScaleX(1);
		
	}
	else
	{
		if (distance <= MONSTER_AI_SHOOT_DISTANCE)
		{
			m_npc->walk(true, true);
			m_npc->walk(true, false);
		}

		m_npc->changeDir(Right);
		setScaleX(-1);
	}

	if (distance <= MONSTER_AI_SHOOT_DISTANCE)
	{
		this->startShoot();
	}
	else
	{
		this->closeShoot();
	}
}

