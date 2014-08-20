#ifndef __ITEMSPRITE__
#define __ITEMSPRITE__ 1

#include "cocos2d.h"
#include "cocostudio.h"

#include "ItemMgr.h"

class ItemSprite: public cocos2d::Sprite
{
public:
	ItemSprite();
	~ItemSprite();
    void init();
    CREATE_FUNC(ItemSprite)

private:

    ItemMgr * m_itemMgr;
};

#endif
