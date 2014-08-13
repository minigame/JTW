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
 * TODO: ���������е���Դ���غ�����װ
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

	//����UI�ļ�����ͬtext.ExportJson
	//���ص�ָ�����ֱ�ӱ�addchild
	cocos2d::ui::Widget* loadUIFromFile(const char * fileName);

	//���ض����ļ�
	//tag����Ҫ�Լ��������ڱ�ʶ������Դ
	//���ڵĿ��Ա�ֱ��addChild
	cocostudio::Armature* loadAnimationFromFile(const std::string& fileName, int tag);

private:
	static ResourceLoader* m_instance;
};
#endif // ResourceLoader_h__

