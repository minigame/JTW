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
 * TODO: ����debug���Log�ĺ�
 *		 ʹ�ã�LOGD("msg"),LOGD(std::string.c_str(),NULL)
 *
 * \note
*/

#if defined(ANDROID)
	#include <android/log.h>
	#define  LOG_TAG    "AndroidDebug"
	#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
	#if defined(WIN32)
		#include <windows.h>
		#define LOGD(msg,null) OutputDebugStringA(msg)
	#else
		#if defined(OSX)
			#define LOGD(msg,null) //haven't impl
		#endif
	#endif
#endif

#endif // Log_h__