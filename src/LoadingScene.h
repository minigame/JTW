#ifndef LoadingSence_h__
#define LoadingSence_h__
/*!
 * \file LoadingSence.h
 * \date 2014/08/13 15:25
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 载入场景
 *
 * \note
*/

#include "cocos2d.h"
#include "ResourceMgr.h"

class LoadingScene : public cocos2d::Scene
{
public:
	LoadingScene();
	~LoadingScene();

	virtual bool init();

	//异步加载完成回调方法
	void resLoaded(float dt);

	CREATE_FUNC(LoadingScene);

private:
	//异步资源加载方法
	void __LoadResourceAsync();
	bool m_isLoaded;
};

#endif // LoadingSence_h__
