#ifndef __TESTSCENE__H
#define __TESTSCENE__H 1

#include "cocos2d.h"
namespace cocos2d {

class testScene: public Scene
{
public:
	testScene();
	~testScene();

	bool init();
	CREATE_FUNC(testScene);

	void onEnter();
	void onExit();
    
private:
    void changeScene(float dt);
};

};

#endif
