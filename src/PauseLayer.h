#ifndef __PAUSELAYER__
#define __PAUSELAYER__ 1

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


NS_CC_BEGIN

class PauseLayer :public Layer
{
public:
	PauseLayer();
	~PauseLayer();

    virtual bool init();
	CREATE_FUNC(PauseLayer);

    void onTouchResume(Ref * obj,  ui::Widget::TouchEventType type);
    void onTouchRestart(Ref * obj, ui::Widget::TouchEventType type);
};

NS_CC_END

#endif
