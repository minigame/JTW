#include "NPCSprite.h"
#include "Tag.h"


NPCSprite::NPCSprite()
{
	m_npc = NULL;
	this->setTag(NPC_TAG);
}


NPCSprite::~NPCSprite()
{
	delete m_npc;
}

bool NPCSprite::init()
{
	if (!Sprite::init())
		return false;

	setCascadeOpacityEnabled(true);
	m_npc = new NPC();


	return true;
}

void NPCSprite::setRole(ROLE r)
{
	m_npc->init(r);
	cocostudio::Armature* armature = m_npc->getArmature();
	addChild(armature);
	m_npc->bindPhyBody(this);
}

void NPCSprite::onHurt()
{
	m_npc->dead();
}


void NPCSprite::createMonsterBo(float dt)
{
	BulletSprite* monsterSprite = new BulletSprite();
	monsterSprite->setType(1);
	monsterSprite->init();


	Vec2 monsterPosition = this->getPosition();
	int direction = 1;
	if (m_npc->getDir() == DIR::Left)
	{
		direction = -1;
	}

	monsterSprite->setPosition(monsterPosition);
	this->getParent()->addChild(monsterSprite);
	monsterSprite->shoot(800 * direction);

}

void NPCSprite::startShoot()
{
	this->schedule(schedule_selector(NPCSprite::createMonsterBo), 1.5f);
}


void NPCSprite::closeShoot()
{
	this->unschedule(schedule_selector(NPCSprite::createMonsterBo));
}
