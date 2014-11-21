#include "CallBackMgr.h"


CallBackMgr::CallBackMgr(void)
{
}


CallBackMgr::~CallBackMgr(void)
{
}

CallBackMgr* CallBackMgr::getInstance()
{
    //return m_instance;
    return CallBackMgrSig::Instance();
}

void CallBackMgr::registerFunction(const std::string& key, void * target, MyCallBackFunc callBack)
{
	if(m_map.size() == 0)
	{
		std::map<void *, MyCallBackFunc> map;
		map[target] = callBack;
		m_map[key] = map;
	}
	else
	{
		m_map[key][target] = callBack;
	}
}

void CallBackMgr::unRegisterFunction(const std::string& key, void * target)
{
	FuncMap::iterator it = m_map.find(key);
	
	if(it != m_map.end())
	{
		std::map<void *,MyCallBackFunc>::iterator iter = it->second.find(target);

		if(iter != it->second.end())
		{
			it->second.erase(iter);
		}
	}
}

void CallBackMgr::tigger( const std::string & key, CallBackData* data)
{
	FuncMap::iterator it = m_map.find(key);

	if (it == m_map.end())
		return;

	std::map<void *,MyCallBackFunc>::iterator iter = it->second.begin();

	for(; iter != it->second.end(); ++iter)
	{
		iter->second(data);
	}
}

void CallBackMgr::unRegForTarget(void * target)
{
	FuncMap::iterator it = m_map.begin();

	for (; it != m_map.end(); ++it)
	{
		std::map<void *, MyCallBackFunc>::iterator iter = it->second.begin();

		for (; iter != it->second.end(); )
		{
			if (iter->first == target)
			{
				iter = it->second.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}
