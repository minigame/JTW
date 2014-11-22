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

#include "ResourceLoader.h"
#include "ResourceMgr.h"
#include "CallBackMgr.h"
#include "DiCiData.h"
//#include <vector>

//初始化资源加载单例
ResourceLoader * ResourceLoader::m_instance = new ResourceLoader();
//初始化资源管理类
ResourceMgr * ResourceMgr::m_instance = new ResourceMgr();

CallBackMgr * CallBackMgr::m_instance = new CallBackMgr();

std::vector<DiCiData*>* diciVector = new std::vector<DiCiData*>();

#endif // Instance_h__
