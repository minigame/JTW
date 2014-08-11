#ifndef MyEventListener_h__
#define MyEventListener_h__
/*!
 * \file MyEventListener.h
 * \date 2014/08/11 19:11
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 事件监听类，用于任何需要监听事件的类进行继承
 *
 * \note
*/

#include <map>
#include "EventMgr.h"

class MyEventListener
{
public:
	MyEventListener();
	~MyEventListener();
protected:
	//用于注册接受事件
	void registerEvent(EVENTID id);
	void unRegisterEvent(EVENTID id);

	//必须重载用来接受&处理事件
	void virtual receiveEvent(EVENTID id, JTWEvent* event) = 0;

	static void callbackFunction(MyEventListener * mySelf, EVENTID id, JTWEvent* event);
private:
	//用于最后析构清除事件注册
	std::map<EVENTID, int> m_regMap;
};

#endif // MyEventListener_h__

