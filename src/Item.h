#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

/*
 * @name: class Item
 * @desc: 实现子弹、以及与游戏角色相交互的"物件"的基类，主要包含
 *        一些通用的数据成员以及加载Armature动画的方法，同时包含
 *        有物理状态，具体的PhysicsBody的类型由派生类定义。
 * @data member:
 *
 * @function member:
 *
 */

class Item
{
public:
    Item();
    virtual ~Item();
	virtual void init();

public:
    /* 设置以及访问Armature的接口 */
	void setArmatureWithExportJsonFile(const char* armatureName);
	void setArmature(cocostudio::Armature* armature);
	cocostudio::Armature * getItemArmature();
 
protected:

    bool isPhyEnable;

    cocostudio::Armature * m_armature;
    CC_SYNTHESIZE(cocos2d::PhysicsBody *, m_phyBox, PhyBox);
    CC_SYNTHESIZE(cocos2d::Vec2, m_position, Position);
};


#endif // Item_h__
