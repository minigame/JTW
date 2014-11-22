#include "WelcomeScene.h"
#include "WelcomeLayer.h"

USING_NS_CC;

WelcomeScene::WelcomeScene()
{
}


WelcomeScene::~WelcomeScene()
{
}

bool WelcomeScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto welcomelayer = WelcomeLayer::create();

	if (!welcomelayer)
		return false;

	this->addChild(welcomelayer);

	return true;
}
