﻿#include "GamePlayerLayer.h"
#include "BulletSprite.h"
#include "GameScene.h"
#include "Log.h"
#include "MonsterSprite.h"
#include "BossSprite.h"
#include "PauseLayer.h"
#include "DiCiData.h"
#include "WelcomeScene.h"

extern std::vector<DiCiData*>* diciVector;

Point playerStart;
std::vector<Point>* monster1Vector = new std::vector<Point>();
std::vector<Point>* monster2Vector = new std::vector<Point>();
std::vector<Point>* bossVector = new std::vector<Point>();

GamePlayerLayer::GamePlayerLayer()
{
	m_world = NULL;
	m_obstacleLayer = NULL;
    m_isPaused = 0;
	m_lastPlayerPosition = Vec2::ZERO;
	m_isNextMission = false;
	m_coinCount = 0;
	m_mapIndex = 1;
}

GamePlayerLayer::~GamePlayerLayer()
{
	this->unscheduleUpdate();
	CallBackMgr::getInstance()->unRegForTarget(this);
}

bool GamePlayerLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	//get the origin point of the X-Y axis, and the visiable size of the screen
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//m_playerSprite = PlayerSprite::create();
	//m_playerSprite->setPosition(Point(origin.x + visiableSize.width / 2 - 300, origin.y + visiableSize.height * 3 / 5));
	//this->addChild(m_playerSprite, 10);

	//createMonster(m_playerSprite->getPosition() + Vec2(400.0f,0), Monster_1);
	//createMonster(m_playerSprite->getPosition() + Vec2(500.0f, 0), Monster_2);
	//createMonster(m_playerSprite->getPosition() + Vec2(600.0f, 0), Boss);

	this->scheduleUpdate();
	CallBackMgr::getInstance()->registerFunction(REMOVE_MONSTER, this, MY_CALL_BACK_1(GamePlayerLayer::removeMonster, this));

	return true;
}

void GamePlayerLayer::createPlayerAndMonsters()
{
	m_playerSprite = PlayerSprite::create();
	Size playerSize = Size(80, 150);
	Size monster1Size = Size(92, 144);
	Size monster2Size = Size(106, 64);
	Size bossSize = Size(75, 132);
	m_playerSprite->setPosition(Point(playerStart.x + 30, playerStart.y + playerSize.height / 2));
	this->addChild(m_playerSprite, 10);
	for (int i = 0; i < monster1Vector->size(); i++)
	{
		createMonster(Point(monster1Vector->at(i).x + 30, monster1Vector->at(i).y + monster1Size.height / 2), Monster_1);
	}
	for (int i = 0; i < monster2Vector->size(); i++)
	{
		createMonster(Point(monster2Vector->at(i).x + 30, monster2Vector->at(i).y + monster2Size.height / 2), Monster_2);
	}
	for (int i = 0; i < bossVector->size(); i++)
	{
		createMonster(Point(bossVector->at(i).x + 30, bossVector->at(i).y + bossSize.height / 2), Boss);
	}
}

void GamePlayerLayer::onTouch()
{

}

void GamePlayerLayer::onLeftButton(bool isCancel)
{
	m_playerSprite->walk(false, isCancel);
}

void GamePlayerLayer::onRightButton(bool isCancel)
{
	m_playerSprite->walk(true, isCancel);
}

void GamePlayerLayer::onActionButton(bool isCancel)
{
	m_playerSprite->attack(isCancel);
}

// 使用递归的方式对node以及其所有的子node执行pause()
// 的操作

void nodeActionPause(Node * node){ node->pause(); }
void nodeActionResume(Node * node){ node->resume(); }

void iterateNodeChildren(Node * node, nodeAction action)
{
    if (node) {
        // 至下往上执行
        auto subChildren = node->getChildren();
        for (auto it = subChildren.begin(); it != subChildren.end(); it++) {
            iterateNodeChildren(*it, action);
        }
        // 最后执行父节点
        action(node);
    }
}

void GamePlayerLayer::onPauseButton()
{
    LOGD("pause button is pressed, stop game");

    // 先关闭所有结点的动作
    iterateNodeChildren(this->getParent(), nodeActionPause);
    auto pauseLayer = this->getParent()->getChildByName("pauseLayer");

    // 只开启pauseLayer的动作
    iterateNodeChildren(pauseLayer, nodeActionResume);
    pauseLayer->setVisible(true);
    return;
}

void GamePlayerLayer::onJumpButton(bool isCancel)
{
	LOGD("jump");
	m_playerSprite->jump(isCancel);
}

void GamePlayerLayer::setPhyWorld(PhysicsWorld* world)
{
	m_world = world;
}

void GamePlayerLayer::setBackLayer(GameBackgroundLayer* layer)
{
	m_backLayer = layer;
}

void GamePlayerLayer::setObstacleLayer(GameObstacleLayer* layer)
{
	m_obstacleLayer = layer;
}

void GamePlayerLayer::setUILayer(GameUILayer* layer)
{
	m_uiLayer = layer;
}

void GamePlayerLayer::setBackRollLayer(Layer** backRollLayer)
{
	m_backRollLayer = backRollLayer;
}

void GamePlayerLayer::update(float dt)
{
	Layer::update(dt);

	Point v = m_playerSprite->getPosition();

	if (m_lastPlayerPosition == v)
		return;

	doMonsterAI(v);
	m_obstacleLayer->updateGears(v);
	setViewPointCenter(v);
	m_lastPlayerPosition = v;

	if (v.x > 14880 && v.y < 960 && !m_isNextMission && m_mapIndex == 1)
	{
		m_isNextMission = true;
		m_playerSprite->getPlayer()->setSucc();
		MissionNumData data;
		data.missionNum = m_mapIndex;
		CallBackMgr::getInstance()->tigger(NEXT_MISSION, &data);
	}

	Size size;
	if (m_playerSprite->getPlayer() != NULL)
	{
		size = m_playerSprite->getPlayer()->getArmature()->getContentSize();

		if (m_playerSprite->getRole() == Monkey)
			size.width = MONKEY_BODY_WIDTH;
		else if (m_playerSprite->getRole() == Pig)
			size.width = PIG_BODY_WIDTH;
	}

	int coins = m_backLayer->checkCoins(v, size);
	if (coins > 0)
	{
		for (int i = 0; i < coins; i++)
		{
			m_coinCount++;
			m_uiLayer->updateCoinLabel(m_coinCount);
		}
	}
	//if (m_playerSprite->ge)
	for (vector<DiCiData*>::iterator iter = diciVector->begin(); iter != diciVector->end(); iter++)
	{
		if (m_playerSprite->getPlayer() == NULL)
			break;
		//if (m_playerSprite->getRole == RO)

		if((*iter)->isHit(v,size))
		{
			int dir;
			if ((*iter)->dir == GearDirection::GEAR_DOWN)
				dir = 4;
			else if ((*iter)->dir == GearDirection::GEAR_UP)
				dir = 8;
			else if((*iter)->dir == GearDirection::GEAR_LEFT)
				dir = 2;
			else if((*iter)->dir == GearDirection::GEAR_RIGHT)
				dir = 1;
			m_playerSprite->beAttacked(dir);
		}
	}

	/*char buffer[256];
	itoa(v.x, buffer, 10);
	char b[256];
	itoa(v.y, b, 10);
	std::string a = "";
	a += buffer;
	a += ",";
	a += b;
	a += "\n";
	LOGD(a.c_str(), NULL);*/
}

void GamePlayerLayer::setViewPointCenter(Point position)
{
	Size winSize = Director::getInstance()->getWinSize();
	TMXTiledMap* _tileMap = m_backLayer->getTiledMap();


	// 防止玩家超出边界
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Point actualPosition = Vec2(x, y);

	Point centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Point viewPoint = centerOfView - actualPosition;
	Point viewPoint2 = viewPoint;

	this->setPosition(viewPoint);

	m_backLayer->setPosition(viewPoint);
	m_obstacleLayer->setPosition(viewPoint);
	for (int i = 0; i < MAX_BACKROLLLAYER; i++) {
		viewPoint2 = Point(viewPoint2.x / 2, viewPoint2.y / 2);
		m_backRollLayer[i]->setPosition(viewPoint2);
	}

	/*LOGD(("position: " + DataConversion::convertPoint2str(position) + "\n").c_str(), NULL);
	LOGD(("actualPosition: " + DataConversion::convertPoint2str(actualPosition) + "\n").c_str(), NULL);
	LOGD(("viewPoint: " + DataConversion::convertPoint2str(viewPoint) + "\n\n").c_str(), NULL);*/
}

void GamePlayerLayer::onChangeRole( ROLE role )
{
	m_playerSprite->changeRole(role);
}


PlayerSprite* GamePlayerLayer::getPlayerSprite()
{
	return m_playerSprite;
}

void GamePlayerLayer::createMonster(Point position, ROLE type)
{
	NPCSprite* npcSprite = NULL;

	switch (type)
	{
	case Monster_1:
		npcSprite = MonsterOneSprite::create();

		break;
	case Monster_2:
		npcSprite = MonsterTwoSprite::create();
		break;
	case Boss:
		npcSprite = BossSprite::create();
		break;
	default:
		break;
	}

	if (npcSprite)
	{
		npcSprite->setPosition(position);
		this->addChild(npcSprite, 0);
		m_monsterList.push_back(npcSprite);
	}
}

void GamePlayerLayer::removeMonster(CallBackData * data)
{
	RemoveMonsterData * removeData = dynamic_cast<RemoveMonsterData*>(data);
	CCASSERT(removeData, "invaild CallBackData");
	m_monsterList.remove(removeData->toBeRemoved);
}

void GamePlayerLayer::doMonsterAI(Point playerPos)
{
	std::list<NPCSprite*>::iterator it = m_monsterList.begin();

	for (; it != m_monsterList.end(); ++it)
	{
		(*it)->AI(playerPos);
	}
}

void GamePlayerLayer::setMissionNum(int num)
{
	m_mapIndex = num;
}
