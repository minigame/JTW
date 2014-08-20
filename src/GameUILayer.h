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
#include "Log.h"
#include "CommonMarco.h"
using namespace cocos2d;

class OptionDelegate
{
public:
    virtual void onTouch() = 0;
    virtual void onLeftButton(bool isCancel) = 0;
    virtual void onRightButton(bool isCancel) = 0;
    virtual void onActionButton(bool isCancel) = 0;
    virtual void onJumpButton(bool isCancel) = 0;
	virtual void onChangeRole(ROLE role) = 0;
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
	void onChangePig(cocos2d::Object* obj, ui::Widget::TouchEventType type);
	void onChangeMonkey(cocos2d::Object* obj, ui::Widget::TouchEventType type);
    
#if defined(WIN32) or defined(__OSX__)
    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
#endif
 
    CC_SYNTHESIZE(OptionDelegate*, delegator, Delegator);

private:
};

#endif // GameUILayer_h__
