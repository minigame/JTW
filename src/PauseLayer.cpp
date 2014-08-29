#include "PauseLayer.h"
#include "GameScene.h"
#include "WelcomeScene.h"
#include "ResourceLoader.h"
#include "Log.h"

USING_NS_CC;
using namespace cocostudio;

PauseLayer::PauseLayer()
{

}

PauseLayer::~PauseLayer()
{

}

bool PauseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    ui::Widget* widget = ResourceLoader::getInstance()->loadUIFromFile("pause_1/pause_1.json");
    addChild(widget);

	ui::Button * btnResume = (ui::Button*)widget->getChildByName("Button_7");
	ui::Button * btnRestart = (ui::Button*)widget->getChildByName("Button_6");

    btnResume->addTouchEventListener(CC_CALLBACK_2(PauseLayer::onTouchResume, this));
    btnRestart->addTouchEventListener(CC_CALLBACK_2(PauseLayer::onTouchRestart, this));
    return true;
}

void PauseLayer::onTouchResume( Ref * obj, ui::Widget::TouchEventType type )
{
    LOGD("touch resume");
    // 先暂停PauseLayer的动作
//    iterateNodeChildren(this, nodeActionPause);
    // 直接重启所有的结点
    auto parent = this->getParent();
 //   iterateNodeChildren(parent, nodeActionResume);
    this->setVisible(false);
}

void PauseLayer::onTouchRestart( Ref * obj, ui::Widget::TouchEventType type )
{
    this->setVisible(false);
//    iterateNodeChildren(this, nodeActionPause);
    LOGD("touch restart");

    // 重启游戏
    //GameScene::gameRestart();

    // 回到主界面
    auto scene = WelcomeScene::create();
    TransitionScene *transition = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(transition);
}
