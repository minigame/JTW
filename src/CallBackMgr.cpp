#include "CallBackMgr.h"


CallBackMgr::CallBackMgr(void)
{
}


CallBackMgr::~CallBackMgr(void)
{
}

CallBackMgr* CallBackMgr::getInstance()
{
	return m_instance;
}

void CallBackMgr::registerFunction(const std::string& key, const std::string& eraseKey, MyCallBackFunc callBack)
{
	if(m_map.size() == 0)
	{
		std::map<std::string, MyCallBackFunc> map;
		map[eraseKey] = callBack;
		m_map[key] = map;
	}
	else
	{
		m_map[key][eraseKey] = callBack;
	}
}

void CallBackMgr::unRegisterFunction( const std::string& key, const std::string& funcKey )
{
	FuncMap::iterator it = m_map.find(key);
	
	if(it != m_map.end())
	{
		std::map<std::string,MyCallBackFunc>::iterator iter = it->second.find(funcKey);

		if(iter != it->second.end())
		{
			it->second.erase(iter);
		}
	}
}

void CallBackMgr::tigger( const std::string & key,CallBackData* data)
{
	FuncMap::iterator it = m_map.find(key);

	if (it == m_map.end())
		return;

	std::map<std::string,MyCallBackFunc>::iterator iter = it->second.begin();

	for(; iter != it->second.end(); ++iter)
	{
		iter->second(data);
	}
}
