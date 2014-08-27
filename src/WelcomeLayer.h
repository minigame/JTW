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
#include "ResourceMgr.h"

using namespace cocostudio;

class WelcomeLayer : public cocos2d::Layer
{
public:
	WelcomeLayer();
	~WelcomeLayer();

	virtual bool init();

	CREATE_FUNC(WelcomeLayer);
	void onCancelTouch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type);
	void onStartTouch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type);

	void onEnter();

private:
	bool m_isLoad;

};
#endif // WelcomeLayer_h__

