#ifndef DataConversion_h__
#define DataConversion_h__

/*!
 * \file ResourceMgr.h
 * \date 2014/08/13 16:10
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 资源管理类
 *
 * \note
*/

#include "cocos2d.h"

#if defined(ANDROID) or defined(__OSX__)
char *itoa(int val, char *buf, unsigned radix);
#endif // ANDROID


class DataConversion
{
private:
	DataConversion();
	~DataConversion();

public:
	static float convertStr2float(const std::string& str);
	static std::string convertPoint2str(cocos2d::Point p);
};
#endif // ResourceMgr_h__
