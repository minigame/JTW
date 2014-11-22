#ifndef ComicScene_h__
#define ComicScene_h__
/*!
 * \file ComicScene.h
 * \date 2014/08/29 20:53
 *
 * \author leozzyzheng
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 漫画场景
 *
 * \note
*/

#include "cocos2d.h"

class ComicScene : public cocos2d::Scene
{
public:
	ComicScene();
	~ComicScene();

	virtual bool init();

	CREATE_FUNC(ComicScene);

	//void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
	void ChangeComicPage(float dt);
	void onEnter();
	void onExit();
private:
	cocos2d::Sprite * m_comic1;
	cocos2d::Sprite * m_comic2;
	int comicIndex;
	bool m_isLoading;
};

#endif // ComicScene_h__
