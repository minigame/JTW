#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
	TMXTiledMap* _tileMap;
	TMXLayer* _meta;
	TMXLayer* _foreground;
	TMXLayer* _background;
	Sprite *_player;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void setViewPointCenter(Point position);
	void setPlayerPosition(Point position);
	void ccTouchesBegan(const std::vector<Touch*>& touches, Event *event);
	void ccTouchesEnded(const std::vector<Touch*>& touches, Event *event);

	Point tileCoordForPosition(Point position);
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
