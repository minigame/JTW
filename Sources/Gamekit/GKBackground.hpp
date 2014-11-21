/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        GKBackground.cpp
 *  Created Time:    2014/11/15  18:03:09
 *  Description:     用于设置背景的基类
 *  Revision:
 *  License:
 */

#ifndef __GKBACKGROUND__
#define __GKBACKGROUND__ 1

NS_CC_BEGIN

class GKBackground: public Sprite
{

public:
    GKBackground();
    ~GKBackground();
    virtual bool init();
    CREATE_FUNC(GKBackground);

// class static function 
    static GKBackground * create(Vec2 origin, Size size, const char *filename);

// public interface function
public:

// private helper function
private:

// private members
private:

};

NS_CC_END;


#endif
