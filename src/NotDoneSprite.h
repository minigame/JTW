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
#include "IUIHaveNotDoneSprite.h"

class NotDoneSprite : public cocos2d::Sprite
{
public:
	static NotDoneSprite* create(cocos2d::Node* node);
	bool initWithNode(cocos2d::Node * node);
	void onEnter();
	void onExit();
private:
	NotDoneSprite();
	~NotDoneSprite();
	
	bool onToucheBegan(cocos2d::Touch*, cocos2d::Event*);

	bool m_isRemove;
	cocos2d::EventListenerTouchOneByOne * m_listener;
	IUIHaveNotDoneSprite * m_ui;

};

#endif // NotDoneSprite_h__
