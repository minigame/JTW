#ifndef WelcomeScene_h__
#define WelcomeScene_h__

/*!
 * \file WelcomeScene.h
 * \date 2014/08/14 19:55
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 游戏主标题
 *
 * \note
*/

#include <cocos2d.h>

class WelcomeScene : public cocos2d::Scene
{
public:
	WelcomeScene();
	~WelcomeScene();

	virtual bool init();

	CREATE_FUNC(WelcomeScene);
};
#endif // WelcomeScene_h__

