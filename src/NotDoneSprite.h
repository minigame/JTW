#ifndef NotDoneSprite_h__
#define NotDoneSprite_h__
/*!
 * \file NotDoneSprite.h
 * \date 2014/08/31 19:09
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 还没做的Sprite
 *
 * \note
*/

#include "cocos2d.h"

class NotDoneSprite : public cocos2d::Sprite
{
public:
	NotDoneSprite();
	~NotDoneSprite();

	virtual bool init();
	void onEnter();
	void onExit();
	CREATE_FUNC(NotDoneSprite);

private:
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

	cocos2d::EventListenerTouchAllAtOnce * m_listener;
	bool m_isRemove;
};

#endif // NotDoneSprite_h__
