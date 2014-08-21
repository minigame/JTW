#include "GameScene.h"
#include "Creature.h"
#include "PhyConst.h"
#include "BulletSprite.h"
#include "Tag.h"

USING_NS_CC;

GameScene::GameScene()
{
	m_backLayer = NULL;
	m_playerLayer = NULL;
	m_uiLayer = NULL;
	m_contactListener = NULL;

}


GameScene::~GameScene()
{
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	if (!this->initWithPhysics())
		return false;

	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("worldGravity_X")),
		DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("worldGravity_Y"))));

	//getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	m_backLayer = GameBackgroundLayer::create();
    m_backLayer->setTag(BACKGROUND_TAG);

	m_playerLayer = GamePlayerLayer::create();
	m_uiLayer = GameUILayer::create();

	PhysicsWorld* gameWorld = getPhysicsWorld();

	if (!m_backLayer || !m_playerLayer || !m_uiLayer)
		return false;

	addChild(m_backLayer,0);
	addChild(m_playerLayer,1);
	addChild(m_uiLayer,2);

	if (!m_backLayer->setTiledMap("map1/map1.tmx"))
	{
		LOGD("Read map failed!\n");
		return false;
	}
	m_backLayer->setPhyWorld(gameWorld);
	m_playerLayer->setPhyWorld(gameWorld);
	m_playerLayer->setBackLayer(m_backLayer);
	m_uiLayer->setDelegator(m_playerLayer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto edgeSp = Sprite::create();
	auto body = PhysicsBody::createEdgeBox(visibleSize, MY_PHYSICSBODY_MATERIAL_DEFAULT, 3);

	body->setCategoryBitmask(GROUND_CATEGORYBITMASK);
	body->setContactTestBitmask(GROUND_CONTACTTESTBITMASK);
	body->setCollisionBitmask(GROUND_COLLISIONBITMASK);
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(body);
    this->addChild(edgeSp);
    edgeSp->setTag(EDGE_TAG);

	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	m_contactListener = EventListenerPhysicsContact::create();
	m_contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_contactListener, this);
}

void GameScene::onExit()
{
	Scene::onExit();
	getEventDispatcher()->removeAllEventListeners();
}

bool getContactObject(Sprite **sp1, Sprite **sp2, Sprite * sprite1, Sprite * sprite2, int taga, int tagb)
{
    if (sp1 && sp2) {
        if ((sprite1->getTag() == taga && sprite2->getTag() == tagb) ||
            (sprite1->getTag() == tagb && sprite2->getTag() == taga))
        {
            if (sprite1->getTag() == taga)
            {
                *sp1 = sprite1;
                *sp2 = sprite2;
            }
            else
            {
                *sp1 = sprite2;
                *sp2 = sprite1;
            }
            return true;
        }
    }
    return false;
}

bool getAnyContactObject(Sprite **sp1, Sprite **sp2, Sprite * sprite1, Sprite * sprite2, int targetTag)
{
    if (sp1 && sp2)
    {
        if (sprite1->getTag() == targetTag)
        {
            *sp1 = sprite1;
            *sp2 = sprite2;
            return true;
        }
        else if (sprite2->getTag() == targetTag)
        {
            *sp1 = sprite2;
            *sp2 = sprite1;
            return true;
        }
    }
    return false;
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();

    // TODO: 这里还不是太清楚句柄的调用机制
    if (!sprite1 || !sprite2) 
	{
        return true;
    }

    Sprite *spriteA, *spriteB;
    printf("contact detected: tagA %d, tagB %d\n", sprite1->getTag(), sprite2->getTag());

    if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, ITEM_TAG, EDGE_TAG))
    {
		BulletSprite * aBulletSprite = dynamic_cast<BulletSprite*>(spriteA);
        if (aBulletSprite)
		{
            // 将子弹去掉，并释放相关资源
            aBulletSprite->removeFromParentAndCleanup(true);
            LOGD("destory bullet now");
        }
        else
        {
            LOGD("no a bullet?");
        }

		return true;
    }

    if (getAnyContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG))
    {
        const PhysicsContactData * data = contact.getContactData();
		PlayerSprite * sprite = dynamic_cast<PlayerSprite*>(spriteA);
		CCASSERT(sprite,"cannot convert Sprite to PlayerSprite at GameScene.cpp");
		sprite->setNormal(data->normal);
		Director::getInstance()->getScheduler()->schedule(schedule_selector(PlayerSprite::onCollisionHandle), sprite, 0, 0, 0, false);
		return true;
    }

	return false;
}
