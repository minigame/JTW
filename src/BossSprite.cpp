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

	//ʵ���Լ���AI

	Point pos = getPosition();

	//�������ҵ�x������ʾ�������ұ�
	if (pos.x > playerPos.x)
	{
		m_npc->changeDir(Left);
		setScaleX(1);
	}
	else
	{
		m_npc->changeDir(Right);
		setScaleX(-1);
	}

	float distance = pos.distance(playerPos);

	if (distance <= MONSTER_AI_SHOOT_DISTANCE)
	{
		this->startShoot();
	}
	else
	{
		this->closeShoot();
	}
}

