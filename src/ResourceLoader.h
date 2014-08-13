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

class ResourceLoader
{
private:
	ResourceLoader();
	~ResourceLoader();
public:
	static ResourceLoader* getInstance();

	//加载UI文件，如同text.ExportJson
	//返回的指针可以直接被addchild
	cocos2d::ui::Widget* loadUIFromFile(const char * fileName);

	//加载动画文件
	//tag是需要自己输入用于标识动画资源
	//反悔的可以被直接addChild
	cocostudio::Armature* loadAnimationFromFile(const std::string& fileName, int tag);

private:
	static ResourceLoader* m_instance;
};
#endif // ResourceLoader_h__

