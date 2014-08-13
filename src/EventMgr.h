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
 * TODO: �¼�������������
 *
 * \note
*/
#include <map>
#include <queue>
#include <vector>
#include "EventDef.h"
#include "cocos2d.h"


class JTWEvent;
class MyEventListener;

typedef void(*JTWEVENT_CALLBACK_FUNC_POINTER)(MyEventListener* ,EVENTID, JTWEvent *);

class EventMgr
{
private:
	EventMgr();
	~EventMgr();
public:
	//�����ڳ���ʼǰȫ�ֳ�ʼ����Ա����
	static EventMgr * getInstance();

	//�ַ���Ϣ
	void sendEvent();

	//ע��ͷ�ע��
	void registerFunction(EVENTID id, JTWEVENT_CALLBACK_FUNC_POINTER function);
	void unRegisterFunction(EVENTID id, JTWEVENT_CALLBACK_FUNC_POINTER function);

	//���ܴ��������Ϣ
public:
	//�����Զ�����Ϣ


	//���պ���һ��ѭ������
	void onPostEvent(EVENTID id, JTWEvent* event, MyEventListener* sender);
	//���պ���������
	void onSendEvent(EVENTID id, JTWEvent* event, MyEventListener* sender);

private:
	static EventMgr* m_instance;

private:
	typedef std::map<EVENTID, std::vector<JTWEVENT_CALLBACK_FUNC_POINTER>> RegisterType;

	struct EventStruct
	{
		EVENTID id;
		JTWEvent * jtwEvent;
		MyEventListener * sender;
	};

	std::map<EVENTID, std::vector<JTWEVENT_CALLBACK_FUNC_POINTER>> m_register; // ��������ע����Ϣ�����ĺ���ָ��
	std::queue<EventStruct> m_message; //��Ϣ����
	
};
#endif // EventMgr_h__

