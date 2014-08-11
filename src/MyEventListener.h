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
 * TODO: �¼������࣬�����κ���Ҫ�����¼�������м̳�
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
	//����ע������¼�
	void registerEvent(EVENTID id);
	void unRegisterEvent(EVENTID id);

	//����������������&�����¼�
	void virtual receiveEvent(EVENTID id, JTWEvent* event) = 0;

	static void callbackFunction(MyEventListener * mySelf, EVENTID id, JTWEvent* event);
private:
	//���������������¼�ע��
	std::map<EVENTID, int> m_regMap;
};

#endif // MyEventListener_h__

