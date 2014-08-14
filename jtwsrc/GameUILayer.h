//
//  OptionLayer.h
//  parasite-city
//
//  Created by Zhou.Zeyong on 14-2-18.
//
//

#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class OptionDelegate
{
public:
    virtual void onTouch() = 0;
    virtual void onLeftButton() = 0;
    virtual void onRightButton() = 0;
    virtual void onActionButton() = 0;
    virtual void onJumpButton() = 0;
};

class GameUILayer :public Layer
{
public:
	GameUILayer();
	~GameUILayer();
    
    virtual bool init();
	CREATE_FUNC(GameUILayer);
    
    // override
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
    
    CC_SYNTHESIZE(OptionDelegate*, delegator, Delegator);
};
