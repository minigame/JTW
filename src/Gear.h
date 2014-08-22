#ifndef Gear_h__
#define Gear_h__

/*!
 * \file Gear.h
 * \date 2014/08/10 20:31
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 可互动物件，吊桥、可破坏石头等
 *
 * \note
*/
#include "Item.h"
#include "cocos2d.h"
#include "PhyConst.h"
#include "Creature.h"
#include "ResourceMgr.h"

//const cocos2d::PhysicsMaterial MY_PHYSICSBODY_MATERIAL_DEFAULT(0.0f, 0.0f, 0.0f);


class Gear :
	public Item
{
public:
	Gear();
	~Gear();


public:
	void addPng2ArmatureWithFileName(const char* name);
	void initWithFile(const char* name);
	void init();
	void setDynamic(bool b);
	bool isDynamic();
	void setPos(cocos2d::Vec2& v);

    Sprite * m_sprite;
};

#endif // Gear_h__
