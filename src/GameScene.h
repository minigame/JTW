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

const int MAX_MAP = 4;
const int MAX_BACKROLLLAYER = 4;
const int MAX_BACKROLLSPLIT = 10;
const int MAP_SIZE[MAX_MAP][MAX_BACKROLLLAYER] = { { 5, 5, 2, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

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
};

#endif // GameScene_h__
