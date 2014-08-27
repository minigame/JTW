#include "LoadingScene.h"
#include "Log.h"
#include "WelcomeScene.h"
#include "ResourceMgr.h"
#include "ResourceLoader.h"
#include "CommonMarco.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
        LOGD("scene init fail");
		return false;
	}

	//下面就需要用的文本资源首先加载
	//所有文本必须放入文件中读取，否则容易乱码！！！
	if (!ResourceMgr::getInstance()->loadStringFile("Strings.xml"))
	{
        LOGD("loading string.xml file fail");
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//*********************For Test**********************
	auto label = LabelTTF::create(ResourceMgr::getInstance()->getString("loadingLabel"), "Arial", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width - label->getContentSize().width / 2,
		origin.y + label->getContentSize().height / 2));

	addChild(label);

	auto fadeOut = FadeOut::create(1.5);
	auto fadeIn = FadeIn::create(1.5);
	auto seq = Sequence::create(fadeOut, fadeIn, NULL);
	auto repeat = RepeatForever::create(seq);
	label->runAction(repeat);

	ResourceLoader::getInstance()->loadArmatureFromFile("monkey_run/monkey_run.ExportJson");
	ResourceLoader::getInstance()->loadArmatureFromFile("monkey_die/monkey_die.ExportJson");
	ResourceLoader::getInstance()->loadArmatureFromFile("monkey_jump/monkey_jump.ExportJson");
	ResourceLoader::getInstance()->loadArmatureFromFile("monkey_noaction/monkey_noaction.ExportJson");
	ResourceLoader::getInstance()->loadArmatureFromFile("monkey_fight/monkey_fight.ExportJson");

	ResourceLoader::getInstance()->loadArmatureFromFile("pig_run/pig_run.ExportJson");
	ResourceLoader::getInstance()->loadArmatureFromFile("pig_die/pig_die.ExportJson");
	ResourceLoader::getInstance()->loadArmatureFromFile("pig_jump/pig_jump.ExportJson");
	ResourceLoader::getInstance()->loadArmatureFromFile("pig_noaction/pig_noaction.ExportJson");
	ResourceLoader::getInstance()->loadArmatureFromFile("pig_fight/pig_fight.ExportJson");

	ResourceLoader::getInstance()->loadArmatureFromFile("monkey_bo/monkey_bo.ExportJson");
	ResourceLoader::getInstance()->loadArmatureFromFile("monster_bo/monster_bo.ExportJson");
    ResourceLoader::getInstance()->loadArmatureFromFile("jiguan/jiguan.ExportJson");

	ResourceLoader::getInstance()->loadArmatureFromFile("monster1_run/monster1.ExportJson");
	ResourceLoader::getInstance()->loadArmatureFromFile("monster2_run/monster2.ExportJson");
    
    // 将UI的控件提取出来统一加载
//    ui::Widget* tmpWidget = ResourceLoader::getInstance()->loadUIFromFile("UI/UI1_1.ExportJson");
//	ResourceLoader::getInstance()->setUiWidget(tmpWidget);
    
//	ResourceLoader::getInstance()->m_uiWidget =
//                    ResourceLoader::getInstance()->loadUIFromFile("UI/UI1_1.ExportJson");

	ResourceMgr::getInstance()->addImage("lift.png", "Lift");
	ResourceMgr::getInstance()->addImage("bridge.png", "bridge");
	ResourceMgr::getInstance()->addImage("zhou.png", "zhou");
	ResourceMgr::getInstance()->addImage("stone.png", "Stone");
	ResourceMgr::getInstance()->addImage("StartMenu/StartBackground.png", "StartBackground");
	
	//预加载UI大图
	ResourceMgr::getInstance()->addImage("StartMenu/ui_20.png", "StartMenu");

	/*   音效的用法
	SimpleAudioEngine::sharedEngine()->preloadEffect(AUDIO_BRIDGE);   这种是预加载
	AudioID::m_audio_bridge = SimpleAudioEngine::sharedEngine()->playEffect(AUDIO_BRIDGE, false);   这个是play
	SimpleAudioEngine::sharedEngine()->stopEffect(AudioID::m_audio_bridge);  //这个是stop
	SimpleAudioEngine::sharedEngine()->pauseEffect(AudioID::m_audio_bridge);  //这个是pause
	*/

	for (int i = 0; i < MAX_BACKROLLLAYER; i++)
	{
		for (int j = 0; j < MAP_SIZE[0][i]; j++)
		{
			char path[100];
			sprintf(path, "map/map_1_%d/map_1_%d_%02d.png", i + 1, i + 1, j + 1);
			ResourceMgr::getInstance()->addImage(path, path);
		}
	}

	ResourceMgr::getInstance()->startLoadImage(CC_CALLBACK_0(LoadingScene::resLoaded, this));

	//**************************************************

    
    LOGD("Loading scene init success");
	return true;
}

void LoadingScene::resLoaded()
{
	//载入下一个场景
    auto scene = WelcomeScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}
