#include "EventMgr.h"


EventMgr::EventMgr()
{
}


EventMgr::~EventMgr()
{
}

EventMgr * EventMgr::getInstance()
{
	return m_instance;
}

void EventMgr::sendEvent()
{
	while (!m_message.empty())
	{
		EventStruct event = m_message.front();
		RegisterType::iterator it = m_register.find(event.id);

		if (it == m_register.end())
		{
			return;
		}
		else
		{
			std::vector<JTWEVENT_CALLBACK_FUNC_POINTER> * vec = &(it->second);
			std::vector<JTWEVENT_CALLBACK_FUNC_POINTER>::iterator vecIt = vec->begin();

			for (; vecIt != vec->end(); ++vecIt)
			{
				if (*vecIt)
				{
					(*vecIt)(event.sender, event.id, event.jtwEvent);
				}
			}
		}

	}
}

void EventMgr::registerFunction(EVENTID id, JTWEVENT_CALLBACK_FUNC_POINTER function)
{
	RegisterType::iterator it = m_register.find(id);

	if (it == m_register.end())
	{
		std::vector<JTWEVENT_CALLBACK_FUNC_POINTER> vec;
		vec.push_back(function);
		m_register[id] = vec;
	}
	else
	{
		std::vector<JTWEVENT_CALLBACK_FUNC_POINTER> * vec = &(it->second);
		std::vector<JTWEVENT_CALLBACK_FUNC_POINTER>::iterator vecIt = vec->begin();
		
		for (; vecIt != vec->end(); ++vecIt)
		{
			if (*vecIt == function)
				return;
		}

		vec->push_back(function);
	}
}

void EventMgr::unRegisterFunction(EVENTID id, JTWEVENT_CALLBACK_FUNC_POINTER function)
{
	RegisterType::iterator it = m_register.find(id);
	
	if (it == m_register.end())
		return;
	else
	{
		std::vector<JTWEVENT_CALLBACK_FUNC_POINTER> * vec = &(it->second);
		std::vector<JTWEVENT_CALLBACK_FUNC_POINTER>::iterator vecIt = vec->begin();

		for (; vecIt != vec->end(); ++vecIt)
		{
			if (*vecIt == function)
			{
				vec->erase(vecIt);
				return;
			}
		}
	}
}

void EventMgr::onPostEvent(EVENTID id, JTWEvent* event, MyEventListener* sender)
{
	EventStruct eventstruct;
	eventstruct.id = id;
	eventstruct.jtwEvent = event;
	eventstruct.sender = sender; 
	m_message.push(eventstruct);
}

void EventMgr::onSendEvent(EVENTID id, JTWEvent* event, MyEventListener* sender)
{
	RegisterType::iterator it = m_register.find(id);

	if (it == m_register.end())
	{
		return;
	}
	else
	{
		std::vector<JTWEVENT_CALLBACK_FUNC_POINTER> * vec = &(it->second);
		std::vector<JTWEVENT_CALLBACK_FUNC_POINTER>::iterator vecIt = vec->begin();

		for (; vecIt != vec->end(); ++vecIt)
		{
			if (*vecIt)
			{
				(*vecIt)(sender, id, event);
			}
		}
	}
}
