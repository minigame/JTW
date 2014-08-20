#ifndef GamePlayerLayer_h__
#define GamePlayerLayer_h__


//#include "AtlasLoader.h"
//#include "SimpleAudioEngine.h"
//#include "CCMenuItem.h"
//#include "GameScene.h"

#include "time.h"
#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "GameUILayer.h"
#include "PlayerSprite.h"
#include "DataConversion.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

const int START_BUTTON_TAG = 100;

class GamePlayerLayer : public Layer, public OptionDelegate {
public:
	GamePlayerLayer(void);
	~GamePlayerLayer(void);
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(GamePlayerLayer);

    void onTouch();
    void onLeftButton(bool isCancel);
    void onRightButton(bool isCancel);
    void onActionButton(bool isCancel);
    void onJumpButton(bool isCancel);

	void setPhyWorld(PhysicsWorld* world);
	void setBackLayer(GameBackgroundLayer* layer);

	void setViewPointCenter(Point position);

public:
	void update(float dt);
private:
	PlayerSprite* m_playerSprite;
	PhysicsWorld* m_world;
	GameBackgroundLayer* m_backLayer;
};

#endif // GamePlayerLayer_h__
