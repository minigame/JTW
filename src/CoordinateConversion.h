#ifndef _COORDINATECONVERSION_H_
#define _COORDINATECONVERSION_H_

#include "cocos2d.h"
using namespace cocos2d;

/***************************************************
*
*
*ע�⣬���ת��������ϵ��Ӧ����������С����������󡪡�������������>
*                                                  |
*                                                  |
*                                                  \/
*****************************************************/

class CoordinateConversion
{
public:
	static Vec2 getLBPosFromCenter(float width, float height, Vec2 centerPos);
	static Vec2 getLTPosFromCenter(float width, float height, Vec2 centerPos);
	static Vec2 getRBPosFromCenter(float width, float height, Vec2 centerPos);
	static Vec2 getRTPosFromCenter(float width, float height, Vec2 centerPos);
	
	static Vec2 getCenterFromLBPos(float width, float height, Vec2 lbPos);
	static Vec2 getCenterFromLTPos(float width, float height, Vec2 ltPos);
	static Vec2 getCenterFromRBPos(float width, float height, Vec2 rbPos);
	static Vec2 getCenterFromRTPos(float width, float height, Vec2 rtPos);
};

#endif