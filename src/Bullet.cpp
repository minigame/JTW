#include "Bullet.h"
#include "PhyConst.h"
USING_NS_CC;

Bullet::Bullet()
{
    Item();
    m_role    = BulletTypeNull;
    m_speed.x = 0;
    m_speed.y = 0;
}

Bullet::Bullet(BulletType type, Vec2 position)
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
    if (m_role == BulletType::BulletTypeNull) {

    }
    else if (m_role == BulletType::BulletTypeMonkeyBo) {
        // 加载猴子的攻击波
        setArmatureWithExportJsonFile("monkey_bo");
        if (m_armature) {
            float radius;
            auto contentSize = m_armature->getContentSize();
            // 加载的图片默认为正方形
            radius = contentSize.width / 2;
            // 加载攻击波的物理body，设置为一个圆形
            m_phyBox = PhysicsBody::createCircle(radius, BULLET_PHYSICSBODY_MATERIAL_DEFAULT);
        }
    }
	else if(m_role == BulletType::BulletTypeMonsterBo)
	{
		setArmatureWithExportJsonFile("monster_bo");
        if (m_armature) {
            
            // 加载攻击波的物理body，设置为一个方形
            //m_phyBox = PhysicsBody::createCircle(radius, BULLET_PHYSICSBODY_MATERIAL_DEFAULT);
			m_phyBox = PhysicsBody::createBox(m_armature->getContentSize(), BULLET_PHYSICSBODY_MATERIAL_DEFAULT);
        }
	}
	else if(m_role == BulletType::BulletTypeBossBo)
	{
		setArmatureWithExportJsonFile("boss_bo");
		if (m_armature) {
			float radius;
			auto contentSize = m_armature->getContentSize();
			// 加载的图片默认为正方形
			radius = contentSize.width / 2;
			// 加载攻击波的物理body，设置为一个圆形
			m_phyBox = PhysicsBody::createCircle(radius, BULLET_PHYSICSBODY_MATERIAL_DEFAULT);
		}
	}

	m_phyBox->setRotationEnable(false);
	// 关闭重力
	m_phyBox->setGravityEnable(false);
	// 设置碰撞属性
	updateBitmask();
}

void Bullet::setSpeed(Vec2 speed)
{
    m_speed = speed;
    // 这里需要根据具体item的构成来同步速度到view中
    // 一般item使用physcialbody来实现view
    if (m_phyBox) {
        m_phyBox->setVelocity(speed);
    }
}

Vec2 Bullet::getSpeed()
{
    if (m_phyBox) {
        m_speed = m_phyBox->getVelocity();
    }
    return m_speed;
}

void Bullet::setSpeedX(float speed)
{
    m_speed.x = speed;
    setSpeed(m_speed);
}

void Bullet::setSpeedY(float speed)
{
    m_speed.y = speed;
    setSpeed(m_speed);
}

void Bullet::updateBitmask()
{
	switch (m_role)
	{
	case BulletTypeNull:
		m_phyBox->setCategoryBitmask(ITEM_CATEGORYBITMASK);
		m_phyBox->setContactTestBitmask(ITEM_CONTACTTESTBITMASK);
		m_phyBox->setCollisionBitmask(ITEM_COLLISIONBITMASK);
		break;
	case BulletTypeMonkeyBo:
		m_phyBox->setCategoryBitmask(ITEM_CATEGORYBITMASK);
		m_phyBox->setContactTestBitmask(ITEM_CONTACTTESTBITMASK);
		m_phyBox->setCollisionBitmask(ITEM_COLLISIONBITMASK);
		break;
	case BulletTypeMonsterBo:
	case BulletTypeBossBo:
		m_phyBox->setCategoryBitmask(MONSTER_BULLET_CATEGORYBITMASK);
		m_phyBox->setContactTestBitmask(MONSTER_BULLET_CONTACTTESTBITMASK);
		m_phyBox->setCollisionBitmask(MONSTER_BULLET_COLLISIONBITMASK);
		break;
	default:
		break;
	}
}
