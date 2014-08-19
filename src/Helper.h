#ifndef Helper_h__
#define Helper_h__

#include "cocos2d.h"

string ptoa(int x, int y) 
{
	std::string msg;
	char buffer[10];
	itoa(x, buffer, 10);
	msg += buffer;
	msg += ",";
	itoa(y, buffer, 10);
	msg += buffer;
	msg += "\0";
	return msg;
}

#endif // Helper_h__
