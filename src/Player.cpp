#include "Player.h"
#include "PhyConst.h"

Player::Player()
{
	m_pigAttackRegion = NULL;
}

Player::~Player()
{
}

void Player::changeAnotherRole()
{
	if (getRole() == Monkey)
	{
		changeRole(Pig);
	} 
	else if (getRole() == Pig)
	{
		changeRole(Monkey);
	}
}

void Player::init()
{
	Creature::init(Monkey);
	changeDir(Right);

	if (m_pigAttackRegion)
	{
		removePigAttackRegion();
	}
}

void Player::onAttackEnd(cocostudio::Armature * armatrue, cocostudio::MovementEventType type, const std::string& id)
{
	//super
	Creature::onAttackEnd(armatrue, type, id);

	switch (getRole())
	{
	case Monkey:
		CallBackMgr::getInstance()->tigger(CREATE_BULLET, NULL);
		break;
	default:
		break;
	}
	
}

void Player::creatPigAttackRegion()
{

	int direction_flag;
	cocos2d::Size attackRegionSize = getArmature()->getContentSize();
	attackRegionSize.width = attackRegionSize.width / 3.0f;
	float attackRegionOffset = attackRegionSize.width * 2.0f;

	if (Left == getDir())
	{
		direction_flag = -1;
	}
	else
	{
		direction_flag = 1;
	}

	//如果当前角色是pig，攻击动画播放完成后，生成近身攻击区域
	m_pigAttackRegion = cocos2d::PhysicsShapeBox::create(attackRegionSize, MY_PHYSICSBODY_MATERIAL_DEFAULT, Vec2(attackRegionOffset * direction_flag, 0.0f));
	m_pigAttackRegion->setCategoryBitmask(ATTACT_REGION_CATEGORYBITMASK);
	m_pigAttackRegion->setContactTestBitmask(ATTACT_REGION_CONTACTTESTBITMASK);
	m_pigAttackRegion->setCollisionBitmask(ATTACT_REGION_COLLISIONBITMASK);
	m_pigAttackRegion->setTag(ATTACKREGION_TAG);
	getPhyBody()->addShape(m_pigAttackRegion);
	////延迟一秒后攻击区域消失
	//Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(Player::removePigAttackRegion, this), this, 0, 0, 1, false, "delayRemoveAttackRegion");

}

void Player::removePigAttackRegion()
{
	getPhyBody()->removeShape(m_pigAttackRegion);
	m_pigAttackRegion = NULL;
}

void Player::deadCompleted()
{
	
}

void Player::onFrameEvent(cocostudio::Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
	//super
	Creature::onFrameEvent(bone, frameEventName, originFrameIndex, currentFrameIndex);

	std::string msg = frameEventName + "\n";
	LOGD(msg.c_str(), NULL);

	//处理猪的三次攻击
	if (frameEventName == PIG_ATTACK_BEGIN_FRAME_EVENT_NAME && getRole() == Pig)
	{
		//攻击开始，攻击次数自增
		beginAttack();
		beginMarkContinueAttack();
		creatPigAttackRegion();
	}
	else if (frameEventName == PIG_ATTACK_END_FRAME_EVENT_NAME && getRole() == Pig)
	{
		removePigAttackRegion();
		dealNextAttack();
		EndMarkContinueAttack();
	}
}

int Player::getMaxAttackCount() const
{
	switch (getRole())
	{
	case Pig:
		return PIG_ATTACK_MAX_COUNT;
		break;
	default:
		return DEFAULT_ATTACK_MAX_COUNT;
		break;
	}
}







