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
#include "ui/CocosGUI.h"

class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();
public:
	static ResourceLoader* getInstance();

	//����UI�ļ�����ͬtext.ExportJson
	//���ص�ָ�����ֱ�ӱ�addchild
	cocos2d::ui::Widget* loadUIFromFile(const char * fileName);

	//���ع��������ļ�
	//ͨ��json�е�name���Ի�ȡ
	void loadArmatureFromFile(const std::string& configFilePath);

	//���ݶ������ƻ�ȡ��plist�ļ�����Ķ���
	cocos2d::Animation* getAnimationByName(const char * name);

	//��׿����Ҫ��������assetĿ¼�µ��ļ��Ա���з���
	//fileName�����·��
	//destPath�����ո�����ɵõ���·��
	bool copyAsset(std::string& fileName, std::string& destPath);

private:
	static ResourceLoader* m_instance;
//    CC_SYNTHESIZE(cocos2d::ui::Widget *, m_uiWidget, UiWidget);

public:
    cocos2d::ui::Widget * m_uiWidget;
};
#endif // ResourceLoader_h__

