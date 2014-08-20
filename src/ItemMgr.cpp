#include "ItemMgr.h"
#include "BulletSprite.h"
#include "Tag.h"
#include "Log.h"

USING_NS_CC;
using namespace cocostudio;
using namespace std;

ItemMgr * ItemMgr::getInstance()
{
    return m_instance;
}

ItemMgr::ItemMgr()
{
    init();
}

ItemMgr::~ItemMgr()
{

}

bool ItemMgr::init()
{
	m_contactListener = EventListenerPhysicsContact::create();
	m_contactListener->onContactBegin = CC_CALLBACK_1(ItemMgr::onContactBegin, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_contactListener, this);
    return true;
}

bool ItemMgr::onContactBegin(PhysicsContact& contact)
{
	// const PhysicsContactData * data = contact.getContactData();
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();

    Sprite *edgeSprite    = NULL;
    Sprite *anotherSprite = NULL;
    
    // TODO: 这里还不是太清楚句柄的调用机制
    if (!sprite1 || !sprite2) 
	{
        return true;
    }
    
    if (sprite1->getTag() == EDGE_TAG) 
	{
        edgeSprite    = sprite1;
        anotherSprite = sprite2;
    }

    if (sprite2->getTag() == EDGE_TAG) 
	{
        edgeSprite    = sprite2;
        anotherSprite = sprite1;
    }

    // 只检测item与edge碰撞的事件
    if (edgeSprite) 
	{
		BulletSprite * aBulletSprite = dynamic_cast<BulletSprite*>(anotherSprite);
        if (aBulletSprite) 
		{
            // 将子弹去掉，并释放相关资源
            aBulletSprite->removeFromParentAndCleanup(true);
            LOGD("destory bullet now");
        }
    }

	return false;
}
