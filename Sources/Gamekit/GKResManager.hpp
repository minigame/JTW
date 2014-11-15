/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        GKResManager.hpp
 *  Created Time:    2014/11/15  14:01:45
 *  Description:     
 *  Revision:
 *  License:
 */

#ifndef __GKRESMANAGER__
#define __GKRESMANAGER__ 1

#include "GKSingleton.hpp"

NS_STD_BEGIN

class GKResManager
{
public:
    GKResManager();
    ~GKResManager();

// public interface function
public:
	//载入文本plist文件
	bool loadStringFile(const char * fileName);
	//从字典里面取出字符串
	std::string getString(const std::string& key);

	// 添加图像文件
	//void addImage(const std::string & fileName, const std::string & name);
	//通过名字来获取图像
	cocos2d::Texture2D* getImage(const std::string & name);
	void addImage(const std::string& fileName, const std::string & name);
	void startLoadImage(std::function<void(void)> callback);

// private helper function
private:
	void _callback(cocos2d::Texture2D * texture);

// private members
private:
	////添加图像的纹理到管理器里
	//void __addImage(cocos2d::Texture2D * texture, const std::string originPath);
	std::function<void(void)> m_loadedCallback;
	static ResourceMgr* m_instance;
	std::map<std::string, std::string> m_strings;
	std::map<std::string, cocos2d::Texture2D*> m_images;
	std::map<std::string, std::string> m_nameMap;
	int m_imageCount;

};

typedef GKSingleton<GKResManager> GKResManagerSingleton;

NS_STD_END;

#endif
