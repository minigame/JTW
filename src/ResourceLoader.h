#ifndef ResourceLoader_h__
#define ResourceLoader_h__
/*!
 * \file ResourceLoader.h
 * \date 2014/08/13 9:06
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 包含了所有的资源加载函数封装
 *
 * \note
*/

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "GKSingleton.hpp"

class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();
public:
	static ResourceLoader* getInstance();

	//加载UI文件，如同text.ExportJson
	//返回的指针可以直接被addchild
	cocos2d::ui::Widget* loadUIFromFile(const char * fileName);

	//加载骨骼动画文件
	//通过json中的name可以获取
	void loadArmatureFromFile(const std::string& configFilePath);

	//根据动画名称获取从plist文件载入的动画
	cocos2d::Animation* getAnimationByName(const char * name);

	//安卓中需要复制所有asset目录下的文件以便进行访问
	//fileName是相对路径
	//destPath是最终复制完成得到的路径
	bool copyAsset(std::string& fileName, std::string& destPath);

private:
    /*static ResourceLoader* m_instance;*/
//    CC_SYNTHESIZE(cocos2d::ui::Widget *, m_uiWidget, UiWidget);

public:
    cocos2d::ui::Widget * m_uiWidget;
};

typedef GKSingleton<ResourceLoader> ResourceLoaderSig;

#endif // ResourceLoader_h__

