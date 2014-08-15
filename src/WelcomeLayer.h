#ifndef WelcomeLayer_h__
#define WelcomeLayer_h__

/*!
 * \file WelcomeLayer.h
 * \date 2014/08/15 9:50
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: ±ÍÃ‚Õº≤„
 *
 * \note
*/
#include <cocos2d.h>

class WelcomeLayer : public cocos2d::Layer
{
public:
	WelcomeLayer();
	~WelcomeLayer();

	virtual bool init();

	CREATE_FUNC(WelcomeLayer);
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
};
#endif // WelcomeLayer_h__

