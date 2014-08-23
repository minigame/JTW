#ifndef CallBackMgr_h__
#define CallBackMgr_h__

#include <string>
#include <map>
#include <functional>
#include "CallBackData.h"
#include "EventDef.h"

//匿名调用类

typedef std::function<void(CallBackData&)> MyCallBackFunc;

#define MY_CALL_BACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)

class CallBackMgr
{
public:
	CallBackMgr(void);
	~CallBackMgr(void);
public:
	static CallBackMgr* getInstance();
	void registerFunction(const std::string& key, const std::string& eraseKey, MyCallBackFunc callBack);
	void unRegisterFunction(const std::string& key, const std::string& eraseKey);
	void tigger(const std::string & key, CallBackData& data);
private:
	typedef std::map<std::string, std::map<std::string, MyCallBackFunc> > FuncMap;
	FuncMap m_map;
	static CallBackMgr * m_instance;
};

#endif // CallBackMgr_h__
