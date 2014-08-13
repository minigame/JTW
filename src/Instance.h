#ifndef Instance_h__
#define Instance_h__

/*!
 * \file Instance.h
 * \date 2014/08/13 22:59
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 包含所有单例类初始化的头文件
 *
 * \note
*/

#include "EventMgr.h"
#include "ResourceLoader.h"
#include "ResourceMgr.h"

//初始化事件管理器单例
EventMgr * EventMgr::m_instance = new EventMgr();
//初始化资源加载单例
ResourceLoader * ResourceLoader::m_instance = new ResourceLoader();
//初始化资源管理类
ResourceMgr * ResourceMgr::m_instance = new ResourceMgr();

#endif // Instance_h__
