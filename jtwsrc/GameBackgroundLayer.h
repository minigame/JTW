//  GameBackgroundLayer.h
//  JTW
//
//  Created by alexzzp on 14-8-13.
//
//

#pragma once

#include "cocos2d.h"
#include "AtlasLoader.h"

using namespace cocos2d;
using namespace std;

class GameBackgroundLayer: public Layer
{
public:
	GameBackgroundLayer(void);
    
	~GameBackgroundLayer(void);
    
	virtual bool init();
    
	CREATE_FUNC(GameBackgroundLayer);
    
    static float getLandHeight();
};
