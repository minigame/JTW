#ifndef LoadingSence_h__
#define LoadingSence_h__
/*!
 * \file LoadingSence.h
 * \date 2014/08/13 15:25
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: ���볡��
 *
 * \note
*/

#include "cocos2d.h"
#include "ResourceMgr.h"

class LoadingSence : public cocos2d::Scene
{
public:
	LoadingSence();
	~LoadingSence();

	virtual bool init();

	//�첽������ɻص�����
	void resLoaded(float dt);

	CREATE_FUNC(LoadingSence);

private:
	//�첽��Դ���ط���
	void __LoadResourceAsync();
	bool m_isLoaded;
};

#endif // LoadingSence_h__
