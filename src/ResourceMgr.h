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
 * TODO: 资源管理类
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

	//载入文本plist文件
	bool loadStringFile(const char * fileName);
	//从字典里面取出字符串
	std::string getString(const std::string& key);

	////添加图像文件
	//void addImage(const std::string & fileName, const std::string & name);
	//
	//通过名字来获取图像
	cocos2d::Texture2D* getImage(const std::string & name);
	void addImage(const std::string& fileName, const std::string & name);
	void startLoadImage(std::function<void(void)> callback);

private:
	void _callback(cocos2d::Texture2D * texture);
	////添加图像的纹理到管理器里
	//void __addImage(cocos2d::Texture2D * texture, const std::string originPath);
	std::function<void(void)> m_loadedCallback;
	static ResourceMgr* m_instance;
	std::map<std::string, std::string> m_strings;
	std::map<std::string, cocos2d::Texture2D*> m_images;
	std::map<std::string, std::string> m_nameMap;
	unsigned int
};
#endif // ResourceMgr_h__

