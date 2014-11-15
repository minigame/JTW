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

#include <string>
#include <vector>

#include "GKSingleton.hpp"

NS_STD_BEGIN

USING_NS_CC;

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
    string getString(const string& key);

    // 添加图像文件
    //void addImage(const string & fileName, const string & name);
    //通过名字来获取图像
    Texture2D* getImage(const string & name);
    void addImage(const string& fileName, const string & name);
    void startLoadImage(function<void(void)> callback);

// private helper function
private:
    void _callback(Texture2D * texture);

// private members
private:
    ////添加图像的纹理到管理器里
    //void __addImage(Texture2D * texture, const string originPath);
    function<void(void)> m_loadedCallback;
    static ResourceMgr* m_instance;
    map<string, string> m_strings;
    map<string, Texture2D*> m_images;
    map<string, string> m_nameMap;
    int m_imageCount;
};

typedef GKSingleton<GKResManager> GKResManagerSingleton;

NS_STD_END;

#endif
