#ifndef __ItemMgr__
#define __ItemMgr__ 1

#include <vector>

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "Item.h"

/*
 * @name: class ItemMgr
 * @desc: 管理Item对象在屏幕边缘的消失事件，若item对象需要在
 *        屏幕的边缘消失的话，则注册到本类中。
 * @data member:
 * @function member:
 */

class ItemMgr: public cocos2d::Node
{
public:
    ItemMgr();
    ~ItemMgr();
    
    void registerItem(Item * item);

// internal helper function
private:
    bool init();
    bool onContactBegin(cocos2d::PhysicsContact & contact);

private:
    std::vector<Item *> m_watchItems;
	cocos2d::EventListenerPhysicsContact* m_contactListener;

// 将ItemMgr包装为单例类
public:
    static ItemMgr * getInstance();
private:
    static ItemMgr * m_instance;
};

#endif
