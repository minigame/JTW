#ifndef __FORTSPRITE__
#define __FORTSPRITE__ 1

#include "cocos2d.h"
#include "Item.h"

class FortSprite: public cocos2d::Sprite
{
public:
	FortSprite(char direction = 0);
	~FortSprite();
    bool init();
    CREATE_FUNC(FortSprite);

    void shoot(float speedX, float speedY = 0.0);

private:

    Item * m_fort;
    char   m_dir;
};

#endif
