#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene()
{
	m_backLayer = NULL;
	m_playerLayer = NULL;
	m_uiLayer = NULL;
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
