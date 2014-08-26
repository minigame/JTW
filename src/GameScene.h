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
#include "GameObstacleLayer.h"
#include "CallBackMgr.h"
#include "CommonMarco.h"

class GameScene :public cocos2d::Scene
{
public:
	GameScene();
	~GameScene();

	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	Layer ** m_backRollLayer;
	GameBackgroundLayer * m_backLayer;
	GamePlayerLayer * m_playerLayer;
	GameUILayer * m_uiLayer;
	GameObstacleLayer* m_obstacleLayer;
	EventListenerPhysicsContact* m_contactListener;

public:
	void onEnter();
	void onExit();
	bool onContactBegin(PhysicsContact& contact);
	void onContactSeperate(PhysicsContact& contact);
	void updateUI();
	void playerBeAttackedAndUpdateUI(CallBackData* data);
};

#endif // GameScene_h__
