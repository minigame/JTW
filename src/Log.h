#ifndef Log_h__
#define Log_h__
/*!
 * \file Log.h
 * \date 2014/08/14 14:38
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 包含debug输出Log的宏
 *		 使用：LOGD("msg"),LOGD(std::string.c_str(),NULL)
 *
 * \note
*/

#if defined(__ANDROID__)
	#include <android/log.h>
	#define  LOG_TAG    "AndroidDebug"
	#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#elif defined(__OSX__)
    #include <iostream>
    #define LOGD(msg, ...) std::cout<<"TWJ DEBUG: "<<msg<<std::endl
#elif defined(WIN32)
    #include <windows.h>
    #define LOGD(msg,null) OutputDebugStringA(msg)
#endif

#endif // Log_h__