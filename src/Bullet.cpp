#include "Bullet.h"
USING_NS_CC;

Bullet::Bullet()
{
    Item();
    m_role    = BulletTypeNull;
    m_speed.x = 0;
    m_speed.y = 0;
}

Bullet::Bullet(BulletType type, Vec2 & position)
{
    m_role     = type;
    m_position = position;
    m_speed.x  = 0;
    m_speed.y  = 0;
}

Bullet::~Bullet()
{
    Item::~Item();
}

void Bullet::init()
{
    // 根据bullet的类型，加载不同的Armature以及设置PhysicsBody
    // 对于BulletTypeNull类型，则不进行操作
    if (m_role == BulletTypeNull) {

    }
    else if (m_role == BulletTypeMonkeyBo) {
        // 加载猴子的攻击波
        setArmatureWithExportJsonFile("monkey_bo/monkey_bo.ExportJson", "monkey_bo");
        if (m_armature) {
            float radius;
            auto contentSize = m_armature->getContentSize();
            // 加载的图片默认为正方形
            radius = contentSize.width / 2;
            // 加载攻击波的物理body，设置为一个圆形
            m_phyBox = PhysicsBody::createCircle(radius, BULLET_PHYSICSBODY_MATERIAL_DEFAULT);
            m_phyBox->setRotationEnable(false);
        }
    }
}

void Bullet::setSpeed(Vec2 speed)
{
    m_speed = speed;
}

Vec2 Bullet::getSpeed()
{
    return m_speed;
}

void Bullet::setSpeedX(float speed)
{
    m_speed.x = speed;
}

void Bullet::setSpeedY(float speed)
{
    m_speed.y = speed;
}

