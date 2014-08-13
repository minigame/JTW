#ifndef ResourceMgr_h__
#define ResourceMgr_h__

/*!
 * \file ResourceMgr.h
 * \date 2014/08/13 16:10
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: ��Դ������
 *
 * \note
*/

#include "cocos2d.h"
#include "../thirdpart/tinyxml/tinyxml.h"

class ResourceMgr
{
private:
	ResourceMgr();
	~ResourceMgr();

public:
	static ResourceMgr* getInstance();

	//�����ı�plist�ļ�
	bool loadStringFile(const char * fileName);
	//���ֵ�����ȡ���ַ���
	std::string getString(const std::string& key);
private:
	static ResourceMgr* m_instance;
	std::map<std::string, std::string> m_strings;
};
#endif // ResourceMgr_h__

