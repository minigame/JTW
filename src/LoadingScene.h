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
	void resLoaded();
	CREATE_FUNC(LoadingScene);
	void tgEnd(float dt);
	void logoEnd(cocostudio::Armature * armatrue, cocostudio::MovementEventType type, const std::string& id);
	void changeScene();


private:
	cocos2d::Sprite * m_tg;
	bool m_isLoading;
};

#endif // LoadingSence_h__
