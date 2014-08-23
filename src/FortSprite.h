#ifndef __FORTSPRITE__
#define __FORTSPRITE__ 1

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

enum FortSpriteDirection {
    left  = -1,
    right = 1
};

#define FORT_DIR_LEFT -1
#define FORT_DIR_RIGHT 1

class FortSprite: public cocos2d::Sprite
{
public:
	FortSprite(FortSpriteDirection direction = FortSpriteDirection::right);
	~FortSprite();
    bool init();
    CREATE_FUNC(FortSprite);

public:
    void shoot(int speed = -1);
    void shootOnTimer(int interval, int repeatCount = -1, int speed = -1);
    void removeShootTimer();
    void setDir(FortSpriteDirection direction);
    
    void onShootHandler(float dt);

private:
    int m_speed;
    FortSpriteDirection m_dir;

    CC_SYNTHESIZE(cocos2d::PhysicsBody *, m_phyBox, PhyBox);
    CC_SYNTHESIZE(cocostudio::Armature *, m_armature, Armature);
    CC_SYNTHESIZE(cocostudio::ArmatureAnimation *, m_armAnimation, ArmAnimation);
};

#endif
