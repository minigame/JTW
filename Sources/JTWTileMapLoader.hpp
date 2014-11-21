/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        JTWTileMapLoader.cpp
 *  Created Time:    2014/11/16  11:50:47
 *  Description:     游戏地图加载器
 *  Revision:
 *  License:
 */

#ifndef __JTWTILEMAPLOADER__
#define __JTWTILEMAPLOADER__ 1

#include "cocos2d.h"

NS_CC_BEGIN

class JTWTileMapLoader
{
public:
    JTWTileMapLoader();
    ~JTWTileMapLoader();

// public interface function
public:

// private helper function
private:

// private members
private:
    // tilemap objects
	TMXLayer* mGround;
	TMXLayer* mPlatform;

	TMXObjectGroup* mPhy;
	TMXObjectGroup* mItem;
	TMXObjectGroup* mPlayer;
	TMXObjectGroup* mObstacle;

    // decrypted Sprite objects
    Sprite *mGroundSprite;

};

NS_CC_END;

#endif
