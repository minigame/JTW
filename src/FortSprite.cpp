#include "FortSprite.h"
#include "PhyConst.h"

USING_NS_CC;

// 构造函数，direction 0 向后, 1 向左
FortSprite::FortSprite(char direction)
{
    m_fort = NULL;
    m_dir  = direction;
}

FortSprite::~FortSprite()
{
    if (m_fort)
    {
        delete m_fort;
    }
}

bool FortSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }

    // 建立机关炮台的动画
    m_fort = new Item();
    m_fort->init();
    m_fort->setArmatureWithExportJsonFile("jiguan");

    // 设置PhysicsBody
    if (m_fort->getItemArmature())
    {
        auto armature = m_fort->getItemArmature();
        auto contentSize = armature->getContentSize();

        armature->getAnimation()->playWithIndex(0);
        addChild(armature);

        // 加载机关炮台的物理body，设置为一个正方形
        auto phyBox = PhysicsBody::createBox(contentSize, MY_PHYSICSBODY_MATERIAL_DEFAULT);

        phyBox->setRotationEnable(false);
        phyBox->setGravityEnable(true);

        // 设置碰撞属性
        phyBox->setCategoryBitmask(ALL_CATEGORYBITMASK);
        phyBox->setContactTestBitmask(ALL_CONTACTTESTBITMASK);
        phyBox->setCollisionBitmask(ALL_COLLISIONBITMASK);

        setPhysicsBody(phyBox);
    }

    return true;
}

// 发射一个炮
void FortSprite::shoot(float speedX, float speedY)
{

}
