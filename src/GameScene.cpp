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

	m_backLayer = GameBackgroundLayer::create();
	m_playerLayer = GamePlayerLayer::create();
	m_uiLayer = GameUILayer::create();
	

	if (!m_backLayer || !m_playerLayer || !m_uiLayer)
		return false;

	addChild(m_backLayer);
	addChild(m_playerLayer);
	addChild(m_uiLayer);

	m_uiLayer->setDelegator(m_playerLayer);

	return true;
}

void GameScene::onEnter()
{
	m_contactListener = EventListenerPhysicsContact::create(); 
	m_contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_contactListener, this); //这个有很多的方法
}

void GameScene::onExit()
{
	//Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	//if(m_contactListener)
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}


bool GameScene::onContactBegin(PhysicsContact& contact)
{
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if(sprite1->getTag() == PLAYERTAG)
	{
		((PlayerSprite*)sprite1)->getPlayer()->onCollisionHandle();
	}

	if(sprite2->getTag() == PLAYERTAG)
	{
		((PlayerSprite*)sprite2)->getPlayer()->onCollisionHandle();
	}
}


