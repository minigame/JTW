#include "MyEventListener.h"


MyEventListener::MyEventListener()
{
}


MyEventListener::~MyEventListener()
{
	std::map<EVENTID, int>::iterator it = m_regMap.begin();

	for (; it != m_regMap.end(); ++it)
	{
		EventMgr::getInstance()->unRegisterFunction(it->first, callbackFunction);
	}

	m_regMap.clear();
}

void MyEventListener::registerEvent(EVENTID id)
{
	EventMgr::getInstance()->registerFunction(id, callbackFunction);
	m_regMap[id] = 0;
}

void MyEventListener::unRegisterEvent(EVENTID id)
{
	EventMgr::getInstance()->unRegisterFunction(id, callbackFunction);
	
	std::map<EVENTID, int>::iterator it = m_regMap.find(id);

	if (it != m_regMap.end())
	{
		m_regMap.erase(it);
	}
}

void MyEventListener::callbackFunction(MyEventListener * mySelf, EVENTID id, JTWEvent* event)
{	
	if (!mySelf)
	{
		//这里肯定会有问题了
#ifdef WIN32
		assert(0);
#endif // WIN32
	}
	else
	{
		mySelf->receiveEvent(id, event);
	}
}

void MyEventListener::sendEvent(EVENTID id, JTWEvent* event)
{
	EventMgr::getInstance()->onSendEvent(id, event, this);
}

void MyEventListener::postEvent(EVENTID id, JTWEvent* event)
{
	EventMgr::getInstance()->onPostEvent(id, event, this);
}
