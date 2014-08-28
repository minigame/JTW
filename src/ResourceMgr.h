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
#include "ResourceLoader.h"
#include "CommonMarco.h"

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

	////���ͼ���ļ�
	//void addImage(const std::string & fileName, const std::string & name);
	//
	//ͨ����������ȡͼ��
	cocos2d::Texture2D* getImage(const std::string & name);
	void addImage(const std::string& fileName, const std::string & name);
	void startLoadImage(std::function<void(void)> callback);

private:
	void _callback(cocos2d::Texture2D * texture);
	////���ͼ���������������
	//void __addImage(cocos2d::Texture2D * texture, const std::string originPath);
	std::function<void(void)> m_loadedCallback;
	static ResourceMgr* m_instance;
	std::map<std::string, std::string> m_strings;
	std::map<std::string, cocos2d::Texture2D*> m_images;
	std::map<std::string, std::string> m_nameMap;
	unsigned int
};
#endif // ResourceMgr_h__

