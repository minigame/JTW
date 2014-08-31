#ifndef IUIHaveNotDoneSprite_h__
#define IUIHaveNotDoneSprite_h__

/*!
 * \file IUIHaveNotDoneSprite.h
 * \date 2014/08/31 21:34
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 所有需要包含"还没有做"图片的UI的Node都需要集成这个接口
 *
 * \note
*/

class IUIHaveNotDoneSprite
{
public:
	IUIHaveNotDoneSprite();
	~IUIHaveNotDoneSprite();

	virtual void setUIWidgetsEnable(bool enable) = 0;
};
#endif // IUIHaveNotDoneSprite_h__

