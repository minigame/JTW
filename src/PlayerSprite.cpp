#include "PlayerSprite.h"
#include "BulletSprite.h"
#include "CommonMarco.h"
//#include "ColorUtils.h"

USING_NS_CC;

PlayerSprite::PlayerSprite()
{
	m_player = NULL;
	m_isOnHurt = false;
	this->setTag(PLAYER_TAG);
}

PlayerSprite::~PlayerSprite()
{
	delete m_player;
	CallBackMgr::getInstance()->unRegForTarget(this);
}

bool PlayerSprite::init()
{
	if (!Sprite::init())
		return false;

	setCascadeOpacityEnabled(true);
	this->setCascadeColorEnabled(true);
	
	//延迟给与人物效果
	this->scheduleOnce(schedule_selector(PlayerSprite::delaySetPlayer), 1);
	
	CallBackMgr::getInstance()->registerFunction(UPDATE_CREATURE_DIRECTION, this, MY_CALL_BACK_1(PlayerSprite::updateDirection,this));
	CallBackMgr::getInstance()->registerFunction(CREATE_BULLET, this, MY_CALL_BACK_1(PlayerSprite::createBullet, this));
	return true;
}

void PlayerSprite::jump(bool isCancel)
{
	m_player->jump(isCancel);
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



void PlayerSprite::updateDirection(CallBackData * data)
{
	CreatureDirData * realData = (CreatureDirData*)(data);
	CCASSERT(realData, "invaild data");

	if (realData->dir == Right)
		setScaleX(1);
	else if (realData->dir == Left)
		setScaleX(-1);
}

void PlayerSprite::attack( bool isCancel )
{
	m_player->attack(isCancel);
}

void PlayerSprite::changeRole( ROLE role )
{
	m_player->changeRole(role);
}

ROLE PlayerSprite::getRole()
{
	return m_player->getRole();
}


//void PlayerSprite::updateBloodUI()
//{
//	//////更新血量UI
//}

Player* PlayerSprite::getPlayer()
{
	return m_player;
}


bool PlayerSprite::beAttacked(int attackDirection)    //受1次攻击
{
	if (openHurt())
	{
		m_player->addbeAttackedNum(attackDirection);
		return true;
	}
	else
	{
		return false;
	}
		
}

bool PlayerSprite::beAttacked(int addnum, int attackDirection)    //受addnum次攻击
{
	if (openHurt())
	{
		m_player->addbeAttackedNum(attackDirection, addnum);
		return true;
	}
	else
	{
		return false;
	}
}

void PlayerSprite::walk(bool isForward, bool isCancel)
{
	m_player->walk(isForward, isCancel);
}

Vec2 PlayerSprite::getSpeed()
{
	return m_player->getSpeed();
}

void PlayerSprite::createBullet(CallBackData * data)
{

	if (Monkey == m_player->getRole())
	{
		auto aBulletSprite = BulletSprite::create();
		Vec2 MonkeyPosition = this->getPosition();
		int direction = 1;

		if (m_player->getDir() == DIR::Left)
		{
			direction = -1;
		}

		MonkeyPosition.x += direction * 55;
		MonkeyPosition.y -= 8;
		aBulletSprite->setPosition(MonkeyPosition);
		this->getParent()->addChild(aBulletSprite);
		aBulletSprite->shoot(800 * direction);
	}
}

void PlayerSprite::onCollisionEnd(Vec2 normal)
{
	m_player->onCollisionEnd(normal);
}

void PlayerSprite::onContactWithElevator(ElevatorSprite* elevator)
{
	m_directionContactWithElevator = elevator->getDirection();
	m_elevator = elevator;
	this->getScheduler()->scheduleUpdate(this, 0, false);
}

void PlayerSprite::SeperateWithElevator()
{
	this->getScheduler()->unscheduleUpdate(this);
}
void PlayerSprite::update(float dt)
{
	Sprite::update(dt);
	//跟随升降梯移动
	if (m_directionContactWithElevator == LeftAndRight)
	{
		this->setPosition(this->getPosition() + Vec2(dt * m_elevator->getSpeed(), 0));
	}
	else if (m_directionContactWithElevator == UpAndDown)
	{
		this->setPosition(this->getPosition() + Vec2(0, dt * m_elevator->getSpeed()));
	}

}



void PlayerSprite::delaySetPlayer(float dt)
{
	m_player = new Player();
	m_player->init();
	cocostudio::Armature* armature = m_player->getArmature();
	addChild(armature);
	m_player->bindPhyBody(this);
}

bool PlayerSprite::openHurt()
{
	if(m_isOnHurt)
		return false;

	m_isOnHurt = true;
	this->schedule(schedule_selector(PlayerSprite::hurtCd), PlAYER_HURT_CD);
	return true;
}


void PlayerSprite::hurtCd(float dt)
{
	m_isOnHurt = false;
	this->unschedule(schedule_selector(PlayerSprite::hurtCd));
}


