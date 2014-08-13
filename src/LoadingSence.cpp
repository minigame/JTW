#include "LoadingSence.h"


LoadingSence::LoadingSence()
{
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

}
