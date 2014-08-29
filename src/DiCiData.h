#ifndef DiCiData_h__
#define DiCiData_h__


#include "cocos2d.h"
#include "GameBackgroundLayer.h"
/*
 * @name: class DiCiData
 * @desc: 地刺数据类
 * @data member:
 *
 * @function member:
 *
 */


class DiCiData
{
public:
	cocos2d::Vec2 pos;
	Size box;
	GearDirection dir;

	DiCiData();
	DiCiData(Vec2 v,Size l,GearDirection d);

	bool isHit(Vec2& p, const Size& s);

	static std::vector<DiCiData*>* diciVector;
};

#endif // Bullet_h__
