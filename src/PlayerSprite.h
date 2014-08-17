#ifndef PlayerSprite_h__
#define PlayerSprite_h__

/*!
 * \file PlayerSprite.h
 * \date 2014/08/15 17:45
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#include "cocos2d.h"
#include "ResourceMgr.h"
#include "Player.h"

class PlayerSprite : public cocos2d::Sprite
{
public:
	PlayerSprite();
	~PlayerSprite();

	virtual bool init();
	void walk();
	void jump();

	CREATE_FUNC(PlayerSprite);

	Player* getPlayer();
private:
	Player * m_player;
};
#endif // PlayerSprite_h__

