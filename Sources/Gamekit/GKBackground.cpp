/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        GKBackground.cpp
 *  Created Time:    2014/11/15  18:03:09
 *  Description:     
 *  Revision:
 *  License:
 */


USING_NS_CC;

/* -------------------------------------------------- */
/* cocso2d framework */

GKBackground::GKBackground()
{

}

GKBackground::~GKBackground()
{

}

bool GKBackground::init()
{
    if (!Sprite::init())
        return false;
    
}

/* -------------------------------------------------- */
/* static class functions */

static GKBackground * GKBackground::create(Vec2 origin, Size size, const char *filename);
{
    GKBackground * bk = NULL;

    bk = GKBackground::create();
    if (bk) {
        bk->setAnchorPoint(Vec2(0, 0));
        bk->setPosition(origin);
    }
    return bk;
}

/* -------------------------------------------------- */
/* static logic */




