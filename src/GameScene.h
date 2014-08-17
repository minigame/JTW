#ifndef GameScene_h__
#define GameScene_h__

/*!
 * \file GameScene.h
 * \date 2014/08/15 17:26
 *
 * \author leozzyzheng coreyzhu
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: ÓÎÏ·Ö÷³¡¾°
 *
 * \note
*/

#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "GamePlayerLayer.h"
#include "GameUILayer.h"

class GameScene :public cocos2d::Scene
{
public:
	GameScene();
	~GameScene();

	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	GameBackgroundLayer * m_backLayer;
	GamePlayerLayer * m_playerLayer;
	GameUILayer * m_uiLayer;
	EventListenerPhysicsContact* m_contactListener;

public:
	void onEnter();
	void onExit();
	bool onContactBegin(PhysicsContact& contact);
};

#endif // GameScene_h__
