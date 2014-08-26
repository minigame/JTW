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
