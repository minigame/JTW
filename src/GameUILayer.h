//
//  OptionLayer.h
//  parasite-city
//
//  Created by Zhou.Zeyong on 14-2-18.
//
//

#ifndef GameUILayer_h__
#define GameUILayer_h__

#include "cocos2d.h"
#include "ResourceLoader.h"
using namespace cocos2d;

class OptionDelegate
{
public:
    virtual void onTouch() = 0;
    virtual void onLeftButton() = 0;
    virtual void onRightButton() = 0;
    virtual void onActionButton() = 0;
    virtual void onJumpButton() = 0;
	virtual void onNoAction() = 0;
};

class GameUILayer :public Layer
{
public:
	GameUILayer();
	~GameUILayer();
    
    virtual bool init();
	CREATE_FUNC(GameUILayer);

	void onATouch(cocos2d::Object* obj, ui::Widget::TouchEventType type);
	void onBTouch(cocos2d::Object* obj, ui::Widget::TouchEventType type);
	void onLeftTouch(cocos2d::Object* obj, ui::Widget::TouchEventType typee);
	void onRightTouch(cocos2d::Object* obj, ui::Widget::TouchEventType type);
    
    CC_SYNTHESIZE(OptionDelegate*, delegator, Delegator);

private:
};

#endif // GameUILayer_h__
