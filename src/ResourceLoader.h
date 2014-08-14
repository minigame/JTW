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

	//���ع��������ļ�
	//tag����Ҫ�Լ��������ڱ�ʶ������Դ
	//���صĿ��Ա�ֱ��addChild
	cocostudio::Armature* loadArmatureFromFile(const std::string& fileName, int tag);

	//���붯��plist�ļ�
	void loadAnimationFromFile(const char * fileName);

	//���ݶ������ƻ�ȡ��plist�ļ�����Ķ���**����Ʒ**
	cocos2d::Animation* getAnimationByName(const char * name);

	//��׿����Ҫ��������assetĿ¼�µ��ļ��Ա���з���
	//fileName�����·��
	//destPath�����ո�����ɵõ���·��
	bool copyAsset(std::string& fileName, std::string& destPath);

private:
	static ResourceLoader* m_instance;
};
#endif // ResourceLoader_h__

