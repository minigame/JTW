#include "DiCiData.h"


DiCiData::DiCiData()
{
	pos = cocos2d::Vec2(0.0f, 0.0f);
	box = Size(0.0f,0.0f);
	dir = GearDirection::GEAR_DOWN;
}
	
DiCiData::DiCiData(Vec2 v,Size l,GearDirection d)
{
	pos = v;
	box = l;
	dir = d;
}


bool DiCiData::isHit(Vec2& p,const Size& s)
{

	float addWidth = (box.width + s.width)/2.0f;
	float addHeight = (box.height + s.height)/2.0f;

	if((p.y + addHeight < pos.y)||(pos.y + addHeight < p.y)||
		(p.x + addWidth < pos.x)||(pos.x + addWidth < p.x))
	{
		return false;
	}
	else
		return true;
}
