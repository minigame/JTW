#include "jtwAppDelegate.h"
#include "LoadingScene.h"

USING_NS_CC;

jtwAppDelegate::jtwAppDelegate() {

}

jtwAppDelegate::~jtwAppDelegate() {

}

bool jtwAppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    //glview->setDesignResolutionSize(288, 512, ResolutionPolicy::SHOW_ALL);
	glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
	glview->setFrameSize(1280, 720);

	// set the resource directory
	this->setResourceSearchResolution();
    
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = LoadingScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void jtwAppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void jtwAppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
void jtwAppDelegate::setResourceSearchResolution()
{
    std::vector<std::string> paths;
    // TODO: 这里直接加入相对路径会一直提示找不到资源文件
    std::string fullpath = "/Users/alexzzp/txworkspace/minigame/svnjtw/trunk/Resources/fbird";
	paths.push_back(fullpath + "fonts");
    paths.push_back(fullpath + "image");
    paths.push_back(fullpath + "sounds");
    
    // FileUtils::getInstance()->setSearchResolutionsOrder(paths);
    FileUtils::getInstance()->setSearchPaths(paths);
}
