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
 * TODO: �������е������ʼ����ͷ�ļ�
 *
 * \note
*/

#include "ResourceLoader.h"
#include "ResourceMgr.h"
#include "CallBackMgr.h"
#include "DiCiData.h"
//#include <vector>

//��ʼ����Դ���ص���
ResourceLoader * ResourceLoader::m_instance = new ResourceLoader();
//��ʼ����Դ������
ResourceMgr * ResourceMgr::m_instance = new ResourceMgr();

CallBackMgr * CallBackMgr::m_instance = new CallBackMgr();

std::vector<DiCiData*>* diciVector = new std::vector<DiCiData*>();

#endif // Instance_h__
