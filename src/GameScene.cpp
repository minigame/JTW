#include "GameScene.h"
#include "Creature.h"

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

	m_backLayer = GameBackgroundLayer::create();
	m_playerLayer = GamePlayerLayer::create();
	m_uiLayer = GameUILayer::create();
	
	PhysicsWorld* gameWorld = getPhysicsWorld();

	if (!m_backLayer || !m_playerLayer || !m_uiLayer)
		return false;

	addChild(m_backLayer,0);
	addChild(m_playerLayer,1);
	addChild(m_uiLayer,2);

	m_backLayer->setPhyWorld(gameWorld);
	m_playerLayer->setPhyWorld(gameWorld);

	m_uiLayer->setDelegator(m_playerLayer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto edgeSp = Sprite::create();
	auto body = PhysicsBody::createEdgeBox(visibleSize, MY_PHYSICSBODY_MATERIAL_DEFAULT, 3);

	body->setCategoryBitmask(GROUND_CATEGORYBITMASK);
	body->setContactTestBitmask(GROUND_CONTACTTESTBITMASK);
	body->setCollisionBitmask(GROUND_COLLISIONBITMASK);
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(body); this->addChild(edgeSp); edgeSp->setTag(0);

	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	m_contactListener = EventListenerPhysicsContact::create(); 
	m_contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_contactListener, this); //这个有很多的方法
}

void GameScene::onExit()
{
	Scene::onExit();
	//Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	//if(m_contactListener)
	getEventDispatcher()->removeAllEventListeners();
}


bool GameScene::onContactBegin(PhysicsContact& contact)
{
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if(sprite1->getTag() == PLAYER_TAG)
	{
		PlayerSprite * sprite = dynamic_cast<PlayerSprite*>(sprite1);
		CCASSERT(sprite,"cannot convert Sprite to PlayerSprite at GameScene.cpp");
		this->getScheduler()->schedule(schedule_selector(PlayerSprite::onCollisionHandle), sprite, 0, 0, 0, false);
	}

	if(sprite2->getTag() == PLAYER_TAG)
	{
		PlayerSprite * sprite = dynamic_cast<PlayerSprite*>(sprite2);
		CCASSERT(sprite, "cannot convert Sprite to PlayerSprite at GameScene.cpp");
		this->getScheduler()->schedule(schedule_selector(PlayerSprite::onCollisionHandle), sprite, 0, 0, 0, false);
	}

	return true;
}

void GameScene::onCollisionHandle(float dt)
{
	
}
