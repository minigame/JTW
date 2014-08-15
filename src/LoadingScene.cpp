#include "LoadingScene.h"
#include "Log.h"
#include "WelcomeScene.h"
#include "ResourceMgr.h"
#include "ResourceLoader.h"

USING_NS_CC;

LoadingScene::LoadingScene()
{
	m_isLoaded = false;
}


LoadingScene::~LoadingScene()
{
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

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

	ResourceLoader::getInstance()->loadArmatureFromFile("monkeyWalk/NewAnimation10.png", "monkeyWalk/NewAnimation10.plist", "monkeyWalk/NewAnimation1.ExportJson");

	Texture2D * texture1 = Director::getInstance()->getTextureCache()->addImage("Title.png");
	ResourceMgr::getInstance()->addImage(texture1, "GameTitle");

	Texture2D * texture2 = Director::getInstance()->getTextureCache()->addImage("HelloWorld.png");
	ResourceMgr::getInstance()->addImage(texture2, "Map");

	//**************************************************
	Director::getInstance()->getScheduler()->schedule(schedule_selector(LoadingScene::resLoaded), this, 0, false);
	return true;
}

void LoadingScene::resLoaded(float dt)
{
	//if (m_isLoaded)
		Director::getInstance()->getScheduler()->unschedule(schedule_selector(LoadingScene::resLoaded), this);
	//else
		//return;

	//载入下一个场景
	auto scene = WelcomeScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

