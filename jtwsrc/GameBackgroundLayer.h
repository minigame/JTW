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

class BackgroundLayer: public Layer
{
public:
	BackgroundLayer(void);
    
	~BackgroundLayer(void);
    
	virtual bool init();
    
	CREATE_FUNC(BackgroundLayer);
    
    static float getLandHeight();
};
