#include "LoadingSence.h"

USING_NS_CC;

LoadingSence::LoadingSence()
{
	m_isInitCompleted = false;
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

	std::thread loadingThread(&LoadingSence::__LoadResourceAsync, this, __ResLoadedCallBack);
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
	
	m_isInitCompleted = true;
	return true;
}

void LoadingSence::__LoadResourceAsync(const std::function<void(LoadingSence*)> & callback)
{
	//TODO 这里加载各种资源




	//回调
	callback(this);
}

void LoadingSence::__ResLoadedCallBack(LoadingSence* self)
{
	if (self->isInited())
	{
	}

	//载入下一个场景
	//Director::getInstance()->replaceScene();
}

bool LoadingSence::isInited()
{
	return m_isInitCompleted;
}
