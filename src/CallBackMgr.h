#ifndef CallBackMgr_h__
#define CallBackMgr_h__

#include <string>
#include <map>
#include <functional>
#include "CallBackData.h"
#include "EventDef.h"

#include "GKSingleton.hpp"

//匿名调用类

typedef std::function<void(CallBackData*)> MyCallBackFunc;

#define MY_CALL_BACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)

class CallBackMgr
{
public:
	CallBackMgr(void);
	~CallBackMgr(void);
public:
	static CallBackMgr* getInstance();
	void registerFunction(const std::string& key, void * target, MyCallBackFunc callBack);
	void unRegisterFunction(const std::string& key, void * target);
	void unRegForTarget(void * target);
	void tigger(const std::string & key, CallBackData* data);
private:
	typedef std::map<std::string, std::map<void *, MyCallBackFunc> > FuncMap;
	FuncMap m_map;
    static CallBackMgr * m_instance;
};

typedef GKSingleton<CallBackMgr> CallBackMgrSig;

#endif // CallBackMgr_h__
