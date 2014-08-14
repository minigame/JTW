#include "LoadingSence.h"
#include "Log.h"
#include "WelcomeScene.h"

USING_NS_CC;

LoadingSence::LoadingSence()
{
	m_isLoaded = false;
}


LoadingSence::~LoadingSence()
{
}

bool LoadingSence::init()
{
	if (!Scene::init())
	{
		return false;
	}

	std::thread loadingThread(&LoadingSence::__LoadResourceAsync, this);
	loadingThread.detach();

	//下面就需要用的文本资源首先加载
	//所有文本必须放入文件中读取，否则容易乱码！！！
	if (!ResourceMgr::getInstance()->loadStringFile("Strings.xml"))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//*********************For Test**********************
	auto label = LabelTTF::create(ResourceMgr::getInstance()->getString("loadingLabel"), "Arial", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width - label->getContentSize().width / 2,
		origin.y + label->getContentSize().height / 2));

	addChild(label);

	auto fadeOut = FadeOut::create(1.5);
	auto fadeIn = FadeIn::create(1.5);
	auto seq = Sequence::create(fadeOut, fadeIn, NULL);
	auto repeat = RepeatForever::create(seq);
	label->runAction(repeat);

	//**************************************************
	Director::getInstance()->getScheduler()->schedule(schedule_selector(LoadingSence::resLoaded), this, 0, false);
	return true;
}

void LoadingSence::__LoadResourceAsync()
{
	//TODO 这里加载各种资源
	//for test sleep 3 second
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));




	m_isLoaded = true;
}

void LoadingSence::resLoaded(float dt)
{
	if (m_isLoaded)
		Director::getInstance()->getScheduler()->unschedule(schedule_selector(LoadingSence::resLoaded), this);
	else
		return;

	//载入下一个场景
	auto scene = WelcomeScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

