//  GameBackgroundLayer.h
//  JTW
//
//  Created by alexzzp on 14-8-13.
//	Modified by leozzyzheng on 14-8-15
//


#ifndef GameBackgroundLayer_h__
#define GameBackgroundLayer_h__

#include "cocos2d.h"

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

#endif // GameBackgroundLayer_h__
