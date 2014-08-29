#include "LoadingScene.h"
#include "Log.h"
#include "WelcomeScene.h"
#include "ResourceMgr.h"
#include "ResourceLoader.h"
#include "CommonMarco.h"

USING_NS_CC;

LoadingScene::LoadingScene()
{
	m_tg = NULL;
	m_actionObj = NULL;
	m_isLoading = false;
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

	m_isLoading = true;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_tg = Sprite::create("TencentGame.png");
	m_tg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(m_tg);

	this->scheduleOnce(schedule_selector(LoadingScene::tgEnd), 2);

	//*********************For Test**********************
	auto label = LabelTTF::create(ResourceMgr::getInstance()->getString("loadingLabel"), "Arial", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width - label->getContentSize().width / 2,
		origin.y + label->getContentSize().height / 2));
	label->setColor(Color3B(0, 0, 0));

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
	ResourceMgr::getInstance()->addImage("ThornsGate.png", "gate");
	ResourceMgr::getInstance()->addImage("StartMenu/StartBackground.png", "StartBackground");
	ResourceMgr::getInstance()->addImage("ThornsGate.png", "gate");
	
	//预加载UI大图
	ResourceMgr::getInstance()->addImage("StartMenu/ui_20.png", "StartMenu1");
	ResourceMgr::getInstance()->addImage("StartMenu/ui_21.png", "StartMenu2");
	ResourceMgr::getInstance()->addImage("Logo/logo0.png", "logo");
	ResourceMgr::getInstance()->addImage("SelectMission/xuanguanka0.png", "xuanguanka");

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
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_BRIDGE);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_BULLET);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_BUTTON_CLICK);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_CHANGE_CHARACTER);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_GAME_OVER);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_GATE);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_JUMP);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_LOGO);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_MONKEY_2ND_JUMP);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_MONKEY_FIGHT);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_PIG_FIGHT_LIGHT);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_PIG_FIGHT_HEAVY);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_PIG_PUSH);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_STONE);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_SUCCESS);

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AUDIO_BACK_MISSION_1);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AUDIO_BACK_MISSION_2);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AUDIO_BACK_TITLE);

	if (m_isLoading)
		m_isLoading = false;
	else
	{
		changeScene();
	}
}

void LoadingScene::tgEnd(float dt)
{
	//载入logo
	m_tg->removeFromParent();
	m_widget = ResourceLoader::getInstance()->loadUIFromFile("Logo/Logo.ExportJson");
	addChild(m_widget);

	//CallFunc* callfunc = CallFunc::create(this, callfunc_selector(LoadingScene::logoEnd));
	m_actionObj = cocostudio::ActionManagerEx::getInstance()->playActionByName("Logo.ExportJson", "Logo");

	this->scheduleOnce(schedule_selector(LoadingScene::logoEnd), 1.5);
}

void LoadingScene::logoEnd(float dt)
{
	/*FadeOut * out = FadeOut::create(1.5);
	CallFunc* callfunc = CallFunc::create(this, callfunc_selector(LoadingScene::changeScene));
	Sequence *seq = Sequence::create(out, callfunc);
	m_widget->runAction(seq);*/

	m_actionObj->stop();
	cocostudio::ActionManagerEx::destroyInstance();

	if (m_isLoading)
		m_isLoading = false;
	else
	{
		m_widget->removeFromParent();
		changeScene();
	}
}

void LoadingScene::changeScene()
{
	//载入下一个场景
	
	auto scene = WelcomeScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}
