#ifndef MissionScene_h__
#define MissionScene_h__

/*!
 * \file MissionScene.h
 * \date 2014/08/29 11:38
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: ¹Ø¿¨Ñ¡Ôñ
 *
 * \note
*/

#include "cocos2d.h"
#include "ResourceMgr.h"
#include "IUIHaveNotDoneSprite.h"

using namespace cocostudio;

class MissionScene : public cocos2d::Scene, public IUIHaveNotDoneSprite
{
public:
	MissionScene();
	~MissionScene();

	virtual bool init();

	void onCancelTouch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type);
	void onStartTouch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type);
	void onM1Touch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type);
	void onM2Touch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type);
	void onM3Touch(cocos2d::Ref * obj, cocos2d::ui::Widget::TouchEventType type);

	CREATE_FUNC(MissionScene);
	virtual void setUIWidgetsEnable(bool enable);
	void onEnter();
	void onExit();
	void isAnimationPlayed();
private:
	int m_mission_num;
	bool m_isLoad;
	cocostudio::Armature *m_pig1;
	cocostudio::Armature *m_pig2;
	ActionObject* m_actionObj;
	cocos2d::ui::Button * m_btnCancel;
	cocos2d::ui::Button * m_btnStart;
	cocos2d::ui::Button * m_btnM1;
	cocos2d::ui::Button * m_btnM2;
	cocos2d::ui::Button * m_btnM3;
	cocos2d::ui::Widget * m_missionwidget;
};
#endif // MissionScene_h__

