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
 * TODO: °üº¬debugÊä³öLogµÄºê
 *
 * \note
*/

#if defined(__GNUC__)
	#include <android/log.h>
	#define  LOG_TAG    "AndroidDebug"
	#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
	#if defined(_MSC_VER)
		#include <windows.h>
		#define LOGD(msg,null) OutputDebugStringA(msg)
	#endif
#endif

#endif // Log_h__
