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
 * TODO: NPC��ʾ��
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

private:
	NPC * m_npc;
};


#endif // NPCSprite_h__

