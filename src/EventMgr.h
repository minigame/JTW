#ifndef EventMgr_h__
#define EventMgr_h__
/*!
 * \file EventMgr.h
 * \date 2014/08/11 19:15
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 事件管理器单例类
 *
 * \note
*/
#include <map>
#include <queue>
#include <vector>
#include "EventDef.h"

class JTWEvent;
class MyEventListener;

typedef void(*JTWEVENT_FUNC_POINTER) (MyEventListener *, EVENTID, JTWEvent *);

class EventMgr
{
private:
	EventMgr();
	~EventMgr();
public:
	//必须在程序开始前全局初始化成员变量
	static EventMgr * getInstance();

	//分发消息
	void sendEvent();

	//注册和反注册
	void registerFunction(EVENTID id, JTWEVENT_FUNC_POINTER function);
	void unRegisterFunction(EVENTID id, JTWEVENT_FUNC_POINTER function);

	//接受处理各种消息
public:
	//处理自定义消息
	void onEvent(EVENTID id, JTWEvent* event, MyEventListener* sender);

private:
	static EventMgr* m_instance;

private:
	typedef std::map<EVENTID, std::vector<JTWEVENT_FUNC_POINTER>> RegisterType;

	struct EventStruct
	{
		EVENTID id;
		JTWEvent * jtwEvent;
		MyEventListener * sender;
	};

	std::map<EVENTID, std::vector<JTWEVENT_FUNC_POINTER>> m_register; // 保存所有注册消息监听的函数指针
	std::queue<EventStruct> m_message; //消息队列
	
};
#endif // EventMgr_h__

