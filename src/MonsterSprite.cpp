#include "MonsterSprite.h"


MonsterOneSprite::MonsterOneSprite()
{
}


MonsterOneSprite::~MonsterOneSprite()
{
}

bool MonsterOneSprite::init()
{
	if (!NPCSprite::init())
		return false;

	setRole(Monster_1);

	return true;
}

void MonsterOneSprite::AI(Point playerPos)
{
	NPCSprite::AI(playerPos);

	//实现自己的AI

	Point pos = getPosition();
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

MonsterTwoSprite::MonsterTwoSprite()
{

}

MonsterTwoSprite::~MonsterTwoSprite()
{

}

bool MonsterTwoSprite::init()
{
	if (!NPCSprite::init())
		return false;

	setRole(Monster_2);

	return true;
}

void MonsterTwoSprite::AI(Point playerPos)
{
	NPCSprite::AI(playerPos);

	Point pos = getPosition();
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
