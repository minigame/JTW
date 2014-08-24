#include "GameScene.h"
#include "Creature.h"
#include "PhyConst.h"
#include "BulletSprite.h"
#include "Tag.h"

USING_NS_CC;

GameScene::GameScene()
{
	m_backLayer2 = NULL;
	m_backLayer = NULL;
	m_playerLayer = NULL;
	m_uiLayer = NULL;
	m_obstacleLayer = NULL;
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

	m_backLayer2 = Layer::create();
	m_backLayer = GameBackgroundLayer::create();
    m_backLayer->setTag(BACKGROUND_TAG);

	m_playerLayer = GamePlayerLayer::create();
	m_uiLayer = GameUILayer::create();
	m_obstacleLayer = GameObstacleLayer::create();

	PhysicsWorld* gameWorld = getPhysicsWorld();

	if (!m_backLayer2 || !m_backLayer || !m_playerLayer || !m_uiLayer)
		return false;

	addChild(m_backLayer2, 0);
	addChild(m_backLayer, 1);
	addChild(m_obstacleLayer,2);
	addChild(m_playerLayer, 3);
	addChild(m_uiLayer, 4);
	if (!m_backLayer->setTiledMap("map/map_1.tmx"))
	{
		LOGD("Read map failed!\n");
		return false;
	}
	m_backLayer->setPhyWorld(gameWorld);
	m_playerLayer->setPhyWorld(gameWorld);
	m_playerLayer->setBackLayer(m_backLayer);
	m_playerLayer->setObstacleLayer(m_obstacleLayer);
	m_playerLayer->setBackLayer2(m_backLayer2);
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

	auto back2 = Sprite::create("map/back2.png");
	TMXTiledMap * tiledMap = m_backLayer->getTiledMap();
	back2->setPosition(Point(back2->getContentSize().width / 2, back2->getContentSize().height / 2));
	m_backLayer2->addChild(back2);

	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	m_contactListener = EventListenerPhysicsContact::create();
	m_contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	m_contactListener->onContactSeperate = CC_CALLBACK_1(GameScene::onContactSeperate, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_contactListener, this); //鈥欌€氣垙藛鈥濃€撯埆鈥光垈鈥÷灯掆垜惟鈭懧?
	//getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_contactListener, this);
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

	if (!sprite1 || !sprite2)
		return false;

    Sprite *spriteA, *spriteB;
    printf("contact detected: tagA %d, tagB %d\n", sprite1->getTag(), sprite2->getTag());

    // 处理item与边沿以及地面碰撞事件
    if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, ITEM_TAG, EDGE_TAG))
    {
        BulletSprite * aBulletSprite = dynamic_cast<BulletSprite*>(spriteA);
        BulletSprite::contactEdgeHandler(aBulletSprite, spriteB);
	}
	else if(getContactObject(&spriteA, &spriteB, sprite1, sprite2, ITEM_TAG, BACKGROUND_TAG))
    {
        BulletSprite * aBulletSprite = dynamic_cast<BulletSprite*>(spriteA);
        BulletSprite::contactEdgeHandler(aBulletSprite, spriteB);
    }

	if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, BRIDGE_TAG))
	{
		//Player* player = dynamic_cast<Player*>(spriteA);
		PlayerSprite* player = dynamic_cast<PlayerSprite*>(spriteA);
		BridgeSprite* bridge = dynamic_cast<BridgeSprite*>(spriteB);

		if (player->getRole() == ROLE::Pig)
		{
			if(fabs(bridge->m_bridge->getRotation()) < 0.5)
			{
				if(player->getPosition().x > bridge->getPosition().x)
					bridge->m_dir = 1;   //向左边旋转
				else
					bridge->m_dir = 0;   //向右边旋转
				Director::getInstance()->getScheduler()->schedule(schedule_selector(BridgeSprite::onCollisionHandle), bridge, 0, 0, 0, false);
			}

		}
	}

    if (getAnyContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG))
    {
        const PhysicsContactData * data = contact.getContactData();
		PlayerSprite * sprite = dynamic_cast<PlayerSprite*>(spriteA);
		CCASSERT(sprite,"cannot convert Sprite to PlayerSprite at GameScene.cpp");
		//sprite->setNormal(data->normal);
		//Director::getInstance()->getScheduler()->schedule(schedule_selector(PlayerSprite::onCollisionHandle), sprite, 0, 0, 0, false);
		sprite->onCollisionHandle(data->normal);
    }

	return true;
}


void GameScene::updateUI()
{
	//if()
	int currentBlood = m_playerLayer->getPlayerSprite()->getPlayer()->getBlood();
	//if(currentBlood == 0)   //没有血了
	m_uiLayer->updateHP(currentBlood);
}

void GameScene::onContactSeperate(PhysicsContact& contact)
{
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (!sprite1 || !sprite2)
		return;

	Sprite *spriteA, *spriteB;
	printf("onContactSeperate detected: tagA %d, tagB %d\n", sprite1->getTag(), sprite2->getTag());

	if (getAnyContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG))
	{
		const PhysicsContactData * data = contact.getContactData();

		if (!data)
			return;

		PlayerSprite * sprite = dynamic_cast<PlayerSprite*>(spriteA);
		CCASSERT(sprite, "cannot convert Sprite to PlayerSprite at GameScene.cpp");
		sprite->onCollisionEnd(data->normal);
	}
}
