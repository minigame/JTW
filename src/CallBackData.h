#ifndef CallBackData_h__
#define CallBackData_h__

#include "CommonMarco.h"

class CallBackData
{
public:
	CallBackData(void);
	~CallBackData(void);
};

class CreatureDirData : public CallBackData
{
public:
	DIR dir;
};

#endif // CallBackData_h


