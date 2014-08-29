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
	CallBackMgr::getInstance()->unRegForTarget(this);
}

bool PlayerSprite::init()
{
	if (!Sprite::init())
		return false;

	setCascadeOpacityEnabled(true);
	m_player = new Player();
	m_player->init();
	cocostudio::Armature* armature = m_player->getArmature();
	addChild(armature);
	m_player->bindPhyBody(this);

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
//	//////����Ѫ��UI
//}

Player* PlayerSprite::getPlayer()
{
	return m_player;
}


void PlayerSprite::beAttacked(int attackDirection)    //��1�ι���
{
	m_player->addbeAttackedNum(attackDirection);
}

void PlayerSprite::beAttacked(int addnum, int attackDirection)    //��addnum�ι���
{
	m_player->addbeAttackedNum(attackDirection, addnum);
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
	//�����������ƶ�
	if (m_directionContactWithElevator == LeftAndRight)
	{
		this->setPosition(this->getPosition() + Vec2(dt * m_elevator->getSpeed(), 0));
	}
	else if (m_directionContactWithElevator == UpAndDown)
	{
		this->setPosition(this->getPosition() + Vec2(0, dt * m_elevator->getSpeed()));
	}

}


