#include "ComicScene.h"
#include "ResourceMgr.h"
#include "WelcomeScene.h"

USING_NS_CC;

ComicScene::ComicScene()
{
	m_comic1 = NULL;
	m_comic2 = NULL;
	m_listener = NULL;
	comicIndex = 0;
	m_isLoading = false;
}


ComicScene::~ComicScene()
{
}

bool ComicScene::init()
{
	if (!Scene::init())
		return false;

	m_comic1 = Sprite::createWithTexture(ResourceMgr::getInstance()->getImage("Comic1"));
	m_comic2 = Sprite::createWithTexture(ResourceMgr::getInstance()->getImage("Comic2"));

	if (!m_comic1 || !m_comic2)
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_comic1->setPosition(visibleSize / 2);
	m_comic2->setPosition(visibleSize / 2);

	addChild(m_comic1, 1);
	addChild(m_comic2, 0);

	++comicIndex;

	return true;
}

void ComicScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
	if (comicIndex == 1)
	{
		++comicIndex;
		m_comic1->removeFromParent();
	}
	else if (comicIndex == 2 && !m_isLoading)
	{
		m_isLoading = true;
		auto scene = WelcomeScene::create();
		TransitionScene *transition = TransitionFade::create(1, scene);
		Director::getInstance()->replaceScene(transition);
	}
}

void ComicScene::onEnter()
{
	Scene::onEnter();

	m_listener = EventListenerTouchAllAtOnce::create();
	m_listener->onTouchesBegan = CC_CALLBACK_2(ComicScene::onTouchesBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
}

void ComicScene::onExit()
{
	Scene::onExit();

	Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
}
