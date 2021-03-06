#include "FortSprite.h"
#include "PhyConst.h"
#include "BulletSprite.h"
#include "Tag.h"

USING_NS_CC;
using namespace cocostudio;

// 构造函数，direction 0 向后, 1 向左
FortSprite::FortSprite(FortSpriteDirection direction)
{
    m_dir   = direction;
    m_speed = -1;

    m_phyBox   = NULL;
    m_armature = NULL;
}

FortSprite::~FortSprite()
{
}

bool FortSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }

    /* 加载动画资源 */
    
    m_armature = Armature::create("jiguan");
    m_armature->setScaleX((float) m_dir);
    addChild(m_armature);
    
    /* 获得动画 */
    m_armAnimation = m_armature->getAnimation();
    
    /* 加载物理特效 */
    
    // 加载机关炮台的物理body，设置为一个正方形
    auto size = m_armature->getContentSize();
    m_phyBox = PhysicsBody::createBox(size, MY_PHYSICSBODY_MATERIAL_DEFAULT);

    //m_phyBox->setRotationEnable(false);
    //m_phyBox->setGravityEnable(false);
    m_phyBox->setDynamic(false);

    // 设置碰撞属性
    m_phyBox->setCategoryBitmask(FORT_CATEGORYBITMASK);
    m_phyBox->setContactTestBitmask(FORT_CONTACTTESTBITMASK);
    m_phyBox->setCollisionBitmask(FORT_COLLISIONBITMASK);

    this->setPhysicsBody(m_phyBox);
    return true;
}

void FortSprite::setDir(FortSpriteDirection direction)
{
    m_dir = direction;
    setScaleX(m_dir);
}

// 根据当前炮台的方向发射一个炮
void FortSprite::shoot(int speed)
{
    m_speed = speed;
    scheduleOnce(schedule_selector(FortSprite::onShootHandler), 1);
}

// 设置一个定时器，以interval的间隔发射子弹
void FortSprite::shootOnTimer()
{
    m_speed = m_shootData.speed;
    schedule(schedule_selector(FortSprite::onShootHandler), m_shootData.interval, m_shootData.repeatCount - 1, 0);
}

void FortSprite::removeShootTimer()
{
    unschedule(schedule_selector(FortSprite::onShootHandler));
}

void FortSprite::onShootHandler(float dt)
{
    auto aBulletSprite = BulletSprite::create();
	aBulletSprite->setType(BulletType::BulletTypeMonsterBo);
    aBulletSprite->setTag(MONSTER_BULLET_TAG);
	aBulletSprite->init();
    this->getParent()->addChild(aBulletSprite);
    
    Vec2 pos = this->getPosition();
    aBulletSprite->setPosition(pos);
    
    // 设置子弹的发射事件
    int direction = m_dir;
    if (m_speed < 0) {
        aBulletSprite->shoot(FORT_BULLET_SPEED * direction);
    } else {
        aBulletSprite->shoot(m_speed * direction);
    }
}

void FortSprite::AI( Point playerPos )
{
	Point pos = getPosition();

	float distance = pos.distance(playerPos);

	if (distance <= MONSTER_AI_SHOOT_DISTANCE)
	{
		this->shootOnTimer();
	}
	else
	{
		this->removeShootTimer();
	}
}

void FortSprite::setShootData( int interval, int repeatCount /*= -1*/, int speed /*= -1*/ )
{
	m_shootData.interval = interval;
	m_shootData.repeatCount = repeatCount;
	m_shootData.speed = speed;
}
