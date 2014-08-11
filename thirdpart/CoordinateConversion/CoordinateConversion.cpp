#include "CoordinateConversion.h"

Vec2 CoordinateConversion::getLBPosFromCenter(float width, float height, Vec2 centerPos)
{
	return Vec2(centerPos.x - 0.5f*width, centerPos.y + 0.5f*height);
}

Vec2 CoordinateConversion::getLTPosFromCenter(float width, float height, Vec2 centerPos)
{
	return Vec2(centerPos.x - 0.5f*width, centerPos.y - 0.5f*height);
}


Vec2 CoordinateConversion::getRBPosFromCenter(float width, float height, Vec2 centerPos)
{
	return Vec2(centerPos.x + 0.5f*width, centerPos.y + 0.5f*height);
}

Vec2 CoordinateConversion::getRTPosFromCenter(float width, float height, Vec2 centerPos)
{
	return Vec2(centerPos.x - 0.5f*width, centerPos.y + 0.5f*height);
}


Vec2 CoordinateConversion::getCenterFromLBPos(float width, float height, Vec2 lbPos)
{
	return Vec2(lbPos.x + 0.5f*width, lbPos.y - 0.5f*height);
}


Vec2 CoordinateConversion::getCenterFromLTPos(float width, float height, Vec2 ltPos)
{
	return Vec2(ltPos.x + 0.5f*width, ltPos.y + 0.5f*height);
}


Vec2 CoordinateConversion::getCenterFromRBPos(float width, float height, Vec2 rbPos)
{
	return Vec2(rbPos.x - 0.5f*width, rbPos.y - 0.5f*height);
}


Vec2 CoordinateConversion::getCenterFromRTPos(float width, float height, Vec2 rtPos)
{
	return Vec2(rtPos.x + 0.5f*width, rtPos.y - 0.5f*height);
}