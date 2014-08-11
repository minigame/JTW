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

	}
	else
	{
		mySelf->receiveEvent(id, event);
	}
}
