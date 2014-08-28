#include "NPCSprite.h"
#include "Tag.h"


NPCSprite::NPCSprite()
{
	m_npc = NULL;
	this->setTag(NPC_TAG);
	m_isShooting = false;
}


NPCSprite::~NPCSprite()
{
	RemoveMonsterData data;
	data.toBeRemoved = this;
	CallBackMgr::getInstance()->tigger(REMOVE_MONSTER, &data);
	closeShoot();
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
	m_npc->changeDir(Left);
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
	BulletSprite* bulletSprite = new BulletSprite();
	bulletSprite->setType(BulletType::BulletTypeMonsterBo);
	bulletSprite->setTag(MONSTER_BULLET_TAG);
	bulletSprite->init();


	Vec2 monsterPosition = this->getPosition();
	int direction = 1;
	if (m_npc->getDir() == DIR::Left)
	{
		direction = -1;
	}

	//Size s = this->getContentSize();
	Size s1 = m_npc->getArmature()->getContentSize();



	if(direction == -1)   //左边
	{
		bulletSprite->setPosition(monsterPosition + Vec2(-1.0f*s1.width/2.0f - 20.0f, 0.0f));
	}
	else   //右边
	{
		bulletSprite->setPosition(monsterPosition + Vec2(1.0f*s1.width/2.0f + 20.0f, 0.0f));
	}
	//monsterSprite->setPosition(monsterPosition);
	this->getParent()->addChild(bulletSprite);
	bulletSprite->shoot(800 * direction);

}

void NPCSprite::startShoot()
{
	if (!m_isShooting)
	{
		this->schedule(schedule_selector(NPCSprite::createMonsterBo), 2.0f);
		m_isShooting = true;
	}
}


void NPCSprite::closeShoot()
{
	this->unschedule(schedule_selector(NPCSprite::createMonsterBo));
	m_isShooting = false;
}

void NPCSprite::AI(Point playerPos)
{
	//具体实现在子类中
}

