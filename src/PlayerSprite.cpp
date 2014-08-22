#include "PlayerSprite.h"
#include "BulletSprite.h"
#include "CommonMarco.h"

USING_NS_CC;

PlayerSprite::PlayerSprite()
{
	m_player = NULL;
	this->setTag(PLAYER_TAG);
}

PlayerSprite::~PlayerSprite()
{
	delete m_player;
}

bool PlayerSprite::init()
{
	if (!Sprite::init())
		return false;
	
	m_player = new Player();
	m_player->init();
	cocostudio::Armature* armature = m_player->getArmature();
	addChild(armature);
	m_player->bindPhyBody(this);

	return true;
}

void PlayerSprite::jump(bool isCancel)
{
	//÷ªƒ‹…Ë÷√Ã¯‘æ≤ªƒ‹Õ®π˝∞¥º¸»°œ�?
	if (!isCancel)
		m_player->changeStatus(STATUS::Jump, true);
}

void PlayerSprite::onCollisionHandle(Vec2 normal)
{
	m_player->onCollisionHandle(normal);
	//Director::getInstance()->getScheduler()->unschedule(schedule_selector(PlayerSprite::onCollisionHandle), this);
}

void PlayerSprite::setNormal(Vec2 normal)
{
	m_normal = normal;
}

void PlayerSprite::leftWalk( bool isCancel )
{
	m_player->changeStatus(STATUS::LeftWalk, !isCancel);
	updateDirection();
}

void PlayerSprite::rightWalk( bool isCancel )
{
	m_player->changeStatus(STATUS::RightWalk, !isCancel);
	updateDirection();
}

void PlayerSprite::updateDirection()
{
	if(m_player->getDir() == Right)
		setScaleX(1);
	else if(m_player->getDir() == Left)
		setScaleX(-1);
}

void PlayerSprite::attack( bool isCancel )
{
	if (!isCancel) {
		m_player->changeStatus(STATUS::Attack, true);
    }
    
    // TODO: 下面的动作应该加到猴子发波的最后一帧的位置
    if (Monkey == m_player->getRole() && isCancel)
    {
        auto aBulletSprite = BulletSprite::create();
        Vec2 MonkeyPosition = this->getPosition();
        //printf("monkeyPosition is x %f, y %f\n", MonkeyPosition.x, MonkeyPosition.y);
        // 根据人物的状态设置方�? 1 向右 -1 向左
        int direction = 1;
        if (m_player->getDir() == DIR::Left || m_player->getDir() == DIR::NoMoveLeft) {
            direction = -1;
        }
        // 将bo从中间的位置发出�?
        // MonkeyPosition.x += direction * 3;
        // MonkeyPosition.y = 2;
        aBulletSprite->setPosition(MonkeyPosition);
        // aBulletSprite->setPosition(0.0, 0.0);
        
        // 加入到图层中，同时设置动�?
        this->getParent()->addChild(aBulletSprite);
        aBulletSprite->shoot(800 * direction);
    }
}

void PlayerSprite::changeRole( ROLE role )
{
	m_player->changeRole(role);
}

ROLE PlayerSprite::getRole()
{
	return m_player->getRole();
}





