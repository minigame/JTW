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

class LoadingSence : public cocos2d::Scene
{
public:
	LoadingSence();
	~LoadingSence();

	virtual bool init();

	CREATE_FUNC(LoadingSence);

private:
	//异步资源加载方法
	void __LoadResourceAsync(const std::function<void(LoadingSence*)> & callback);
	//异步加载完成回调方法
	static void __ResLoadedCallBack(LoadingSence* self);
};

#endif // LoadingSence_h__
