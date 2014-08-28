#ifndef NPCSprite_h__
#define NPCSprite_h__

/*!
 * \file NPCSprite.h
 * \date 2014/08/26 16:53
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: NPCœ‘ æ¿‡
 *
 * \note
*/

#include "cocos2d.h"
#include "NPC.h"

class NPCSprite : public cocos2d::Sprite
{
public:
	NPCSprite();
	~NPCSprite();

	virtual bool init();
	void setRole(ROLE r);
	CREATE_FUNC(NPCSprite);
	void onHurt();

	void createMonsterBo(float dt);
	void startShoot();
	void closeShoot();
	virtual void AI(Point playerPos);

private:
	NPC * m_npc;
	bool m_isShooting;
};


#endif // NPCSprite_h__


