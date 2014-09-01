#include "GameScene.h"
#include "Creature.h"
#include "PhyConst.h"
#include "BulletSprite.h"
#include "Tag.h"
#include "GateSprite.h"
#include "Log.h"
#include "PauseLayer.h"
#include "MissionScene.h"

USING_NS_CC;

GameScene::GameScene()
{
	m_backRollLayer = new Layer*[MAX_BACKROLLLAYER];
	m_backLayer = NULL;
	m_playerLayer = NULL;
	m_uiLayer = NULL;
	m_obstacleLayer = NULL;
	m_contactListener = NULL;
	m_mapIndex = 1;
}

GameScene::GameScene(int mapIndex)
{
	m_backRollLayer = new Layer*[MAX_BACKROLLLAYER];
	m_backLayer = NULL;
	m_playerLayer = NULL;
	m_uiLayer = NULL;
	m_obstacleLayer = NULL;
	m_contactListener = NULL;
	m_mapIndex = mapIndex;
}

GameScene::~GameScene()
{
    LOGD("game scene is destoryed");
	//取消掉这些函数的注册
	CallBackMgr::getInstance()->unRegForTarget(this);
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	if (!this->initWithPhysics())
		return false;

	m_contactListener = EventListenerPhysicsContact::create();
	m_contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	m_contactListener->onContactSeperate = CC_CALLBACK_1(GameScene::onContactSeperate, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_contactListener, this);

	//getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	this->getPhysicsWorld()->setGravity(Vec2(DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("worldGravity_X")),
		DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("worldGravity_Y"))));

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//z轴计数
	int count = 0;

	int i, j;
	bool allCreated = true;
	for (i = 0; i < MAX_BACKROLLLAYER; i++) {
		m_backRollLayer[i] = Layer::create();
		allCreated = allCreated && m_backRollLayer[i];
	}
	m_playerLayer = GamePlayerLayer::create();
	m_uiLayer = GameUILayer::create();
	m_obstacleLayer = GameObstacleLayer::create();
	m_backLayer = GameBackgroundLayer::create();
    
	PhysicsWorld* gameWorld = getPhysicsWorld();

	if (!allCreated || !m_backLayer || !m_playerLayer || !m_uiLayer || !m_obstacleLayer)
		return false;

	m_backLayer->setTag(BACKGROUND_TAG);
	m_playerLayer->setMissionNum(m_mapIndex);
	m_uiLayer->setMissionNum(m_mapIndex);

	for (i = 0; i < MAX_BACKROLLLAYER; i++) {
		addChild(m_backRollLayer[MAX_BACKROLLLAYER - i - 1], count++);
	}

	m_backLayer->setObstacleLayer(m_obstacleLayer);


	if(m_mapIndex == 1)
	{
		if (!m_backLayer->setTiledMap("map/map_1.tmx"))
		{
			LOGD("Read map1 failed!\n");
			return false;
		}
	}
	else if(m_mapIndex == 2)
	{
		if (!m_backLayer->setTiledMap("map/map_2.tmx"))
		{
			LOGD("Read map2 failed!\n");
			return false;
		}
	}
	

	addChild(m_backLayer, count++, "backLayer");
	addChild(m_obstacleLayer, count++, "obstacleLayer");
	addChild(m_playerLayer, count++, "playerLayer");
	addChild(m_uiLayer, count++, "uiLayer");

    auto pauseLayer = PauseLayer::create();
    addChild(pauseLayer, count++, "pauseLayer");
    pauseLayer->setVisible(false);

	m_backLayer->setPhyWorld(gameWorld);
	m_playerLayer->setPhyWorld(gameWorld);
	m_playerLayer->setBackLayer(m_backLayer);
	m_playerLayer->setObstacleLayer(m_obstacleLayer);
	m_playerLayer->setBackRollLayer(m_backRollLayer);
	m_playerLayer->setUILayer(m_uiLayer);
	m_uiLayer->setDelegator(m_playerLayer);

	auto edgeSp = Sprite::create();
	auto body = PhysicsBody::createEdgeBox(visibleSize + Size(0, DEATH_DISTANCE), MY_PHYSICSBODY_MATERIAL_DEFAULT, 3);

	body->setCategoryBitmask(EDGE_CATEGORYBITMASK);
	body->setContactTestBitmask(EDGE_CONTACTTESTBITMASK);
	body->setCollisionBitmask(EDGE_COLLISIONBITMASK);
	edgeSp->setPosition(Point(visibleSize.width / 2, (visibleSize.height) / 2 - DEATH_DISTANCE));
	edgeSp->setPhysicsBody(body);
    this->addChild(edgeSp);
    edgeSp->setTag(EDGE_TAG);

	for (i = 0; i < MAX_BACKROLLLAYER; i++)
	{
		int offset = 0;
		for (j = 0; j < MAP_SIZE[m_mapIndex - 1][i]; j++)
		{
			char path[100];
			sprintf(path, "map/map_%d_%d/map_%d_%d_%02d.png", m_mapIndex, i + 1, m_mapIndex, i + 1, j + 1);
			
			Texture2D * texture = ResourceMgr::getInstance()->getImage(path);
			Sprite * BackRollSplit = NULL;

			if (m_mapIndex == 2 || (m_mapIndex == 1 && i + 1 == 3))
			{
				Rect rect = Rect::ZERO;
				rect.size = Size(60 * 256, 60 * 32);
				BackRollSplit = Sprite::createWithTexture(texture, rect);
				Texture2D::TexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
				BackRollSplit->getTexture()->setTexParameters(tp);
			}
			else
			{
				BackRollSplit = Sprite::createWithTexture(texture);
			}

			BackRollSplit->setPosition(Point(offset + BackRollSplit->getContentSize().width / 2, BackRollSplit->getContentSize().height / 2));
			offset += BackRollSplit->getContentSize().width;
			m_backRollLayer[i]->addChild(BackRollSplit);
		}
	}
	m_playerLayer->createPlayerAndMonsters();
	CallBackMgr::getInstance()->registerFunction(PLAYER_BE_ATTACKED, this, MY_CALL_BACK_1(GameScene::playerBeAttackedAndUpdateUI, this));
	CallBackMgr::getInstance()->registerFunction(GAME_RESTART, this, MY_CALL_BACK_1(GameScene::gameRestart, this));

	return true;
}


void GameScene::enterSecondMap()
{
	if (m_uiLayer)
		m_uiLayer->enterSecondMap();
}


void GameScene::onEnter()
{
	Scene::onEnter();

	if (m_mapIndex == 1)
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACK_MISSION_1, true);
	else
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACK_MISSION_2, true);
}

void GameScene::onExit()
{
	Scene::onExit();

	//这里背景音乐不应该交给这里控制，因为这里无法预期什么时候被调用
	//CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    // WARN: 这里不能调用removeAllEventListeners()的方法，否则再重启游戏
    //       重新建立GameScene的时候会失去控制，暂时还不明白原因
    //getEventDispatcher()->removeAllEventListeners();
}

bool getContactObject(Sprite **sp1, Sprite **sp2, Sprite * sprite1, Sprite * sprite2, int taga, int tagb)
{
    if (sp1 && sp2) {
        if ((sprite1->getTag() == taga && sprite2->getTag() == tagb) ||
            (sprite1->getTag() == tagb && sprite2->getTag() == taga))
        {
            if (sprite1->getTag() == taga)
            {
                *sp1 = sprite1;
                *sp2 = sprite2;
            }
            else
            {
                *sp1 = sprite2;
                *sp2 = sprite1;
            }
            return true;
        }
    }
    return false;
}

bool getAnyContactObject(Sprite **sp1, Sprite **sp2, Sprite * sprite1, Sprite * sprite2, int targetTag, bool & needNagNormal)
{
    if (sp1 && sp2)
    {
        if (sprite1->getTag() == targetTag)
        {
            *sp1 = sprite1;
            *sp2 = sprite2;
			needNagNormal = true;
            return true;
        }
        else if (sprite2->getTag() == targetTag)
        {
            *sp1 = sprite2;
            *sp2 = sprite1;
			needNagNormal = false;
            return true;
        }
    }
    return false;
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
    auto contactNormal = contact.getContactData()->normal;
    
	if (!sprite1 || !sprite2)
		return false;

    Sprite *spriteA, *spriteB;
	bool needNagNormal = false;
	char buffer[256];
    sprintf(buffer, "contact detected: tagA %d, tagB %d, direction (%f, %f)\n",
            sprite1->getTag(), sprite2->getTag(), contactNormal.x, contactNormal.y);

	//LOGD(buffer,NULL);

    // 处理item与边沿以及地面碰撞事件
	if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, ITEM_TAG, EDGE_TAG) 
		|| getContactObject(&spriteA, &spriteB, sprite1, sprite2, MONSTER_BULLET_TAG, EDGE_TAG))
    {
        BulletSprite * aBulletSprite = dynamic_cast<BulletSprite*>(spriteA);
		CCASSERT(aBulletSprite,"invaild bullet");
        aBulletSprite->contactHandler();
		return true;//必须return，对象已经销毁了
	}
	else if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, ITEM_TAG, BACKGROUND_TAG) 
		|| getContactObject(&spriteA, &spriteB, sprite1, sprite2, MONSTER_BULLET_TAG, BACKGROUND_TAG))
    {
        BulletSprite * aBulletSprite = dynamic_cast<BulletSprite*>(spriteA);
        aBulletSprite->contactHandler();
		return true;
    }
	else if(getContactObject(&spriteA, &spriteB, sprite1, sprite2, ITEM_TAG, NPC_TAG))
	{
		BulletSprite * aBulletSprite = dynamic_cast<BulletSprite*>(spriteA);
		CCASSERT(aBulletSprite,"invaild bullet");
		aBulletSprite->contactHandler();
		NPCSprite * npc = dynamic_cast<NPCSprite*>(spriteB);
		CCASSERT(npc, "invaild npc");
		npc->onHurt();
		return true;
	}
	else if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, MONSTER_BULLET_TAG, PLAYER_TAG))
	{
		BulletSprite * aBulletSprite = dynamic_cast<BulletSprite*>(spriteA);
		CCASSERT(aBulletSprite, "invaild bullet");
		int direction = aBulletSprite->getDirection();
		
		PlayerSprite * player = dynamic_cast<PlayerSprite*>(spriteB);
		CCASSERT(player, "invaild player");

		if(player->beAttacked(direction))
			aBulletSprite->contactHandler();

		return true;
	}
	else if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, BRIDGE_TAG))
	{
		//Player* player = dynamic_cast<Player*>(spriteA);
		PlayerSprite* player = dynamic_cast<PlayerSprite*>(spriteA);
		BridgeSprite* bridge = dynamic_cast<BridgeSprite*>(spriteB);

		if (player->getRole() == ROLE::Pig)
		{
			if(fabs(bridge->m_bridge->getRotation()) < 0.5)
			{
				if(player->getPosition().x > bridge->getPosition().x)
					bridge->m_dir = 1;   //向左边旋转
				else
					bridge->m_dir = 0;   //向右边旋转

				bridge->onCollisionHandle(NULL);
				//CallBackMgr::getInstance()->tigger(BRIDGE_ROTATE, NULL);
				//player->onCollisionHandle(contact.getContactData()->normal);
				//Director::getInstance()->getScheduler()->schedule(schedule_selector(BridgeSprite::onCollisionHandle), bridge, 0, 0, 0, false);
			}
		}
	}
	else if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, ELEVATOR_TAG))
	{
		PlayerSprite * player = dynamic_cast<PlayerSprite*>(spriteA);
		ElevatorSprite * elevator = dynamic_cast<ElevatorSprite*>(spriteB);
		LOGD("Elevator and player contact!\n");
		Vec2 realNormal = contact.getContactData()->normal;
		
		//以猴子为主观对象，判断碰撞法向量方向
		if (ELEVATOR_TAG != sprite1->getTag())
		{
			realNormal = Vec2(-realNormal.x, -realNormal.y);
		}

		if (abs(realNormal.y) >= 0.5f)//有效值目前只看到1
		{
			if (realNormal.y > 0)//player脚踩升降梯
			{
				LOGD("up collision\n");
				player->onContactWithElevator(elevator);
			}
			else if (realNormal.y < 0)//player头顶碰撞升降梯
			{
				LOGD("down collision\n");
				if (UpAndDown == elevator->getDirection() && elevator->getSpeed() < 0 && Vec2(0, 0) == player->getSpeed())
				{
					elevator->turnarounddiection();
				}
			}
		}
		//else if (abs(realNormal.x) >= 0.5f)
		//{
		//	if (realNormal.x < 0)//player被撞向左边
		//	{
		//		LOGD("left collision\n");
		//		if (elevator->getSpeed() < 0 && elevator->getDirection() == LeftAndRight)
		//		{
		//			player->onContactWithElevator(elevator);
		//		}
		//		else
		//		{
		//			player->SeperateWithElevator();
		//		}
		//	}
		//	else if (realNormal.x > 0)//player被撞向右边
		//	{
		//		LOGD("right collision\n");
		//		if (elevator->getSpeed() > 0 && elevator->getDirection() == LeftAndRight)
		//		{
		//			player->onContactWithElevator(elevator);
		//		}
		//		else
		//		{
		//			player->SeperateWithElevator();
		//		}
		//	}
		//}
	}
	else if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, GATE_TAG))
	{
		PlayerSprite* player = dynamic_cast<PlayerSprite*>(spriteA);
		Vec2 realNormal = contact.getContactData()->normal;
		if (needNagNormal)
			realNormal = Vec2(-realNormal.x, -realNormal.y);

		if (abs(realNormal.x) >= 0.5f)//有效值目前只看到1
		{

			if (realNormal.x > 0)//右边碰撞
			{
				player->beAttacked(1);
			}
			else if (realNormal.x < 0)//左边碰撞
			{
				player->beAttacked(2);
			}
		}
		else if (abs(realNormal.y) >= 0.5f)
		{
			//setSpeedY(0.0f);

			if (realNormal.y > 0)//上边碰撞
			{
				player->beAttacked(4);
			}
			else if (realNormal.y < 0)//下边碰撞
			{
				player->beAttacked(8);
			}
		}
	}
	else if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, EDGE_TAG))
	{
		const PhysicsContactData * data = contact.getContactData();

		if (!data)
			return false;

		Point p = data->points[0];

		if (abs(p.y + DEATH_DISTANCE) <= 50.0f)
		{
			PlayerSprite * sprite = dynamic_cast<PlayerSprite*>(spriteA);
			CCASSERT(sprite, "invaild Player Sprite");
			//死掉
			sprite->beAttacked(1000, 0);
			return true;
		}
	}
	else if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, STONE_TAG))
    {
		LOGD("player and stone contact!\n");
        // 处理玩家与石头之间的碰撞关系，只有八戒能够触发推石头的操作
        PlayerSprite* player = dynamic_cast<PlayerSprite*>(spriteA);
        StoneSprite*  stone  = dynamic_cast<StoneSprite*>(spriteB);

        // 若normal是从stone指向player，这里需要进行切换
        if (sprite1->getTag() == STONE_TAG) {
            contactNormal = Vec2(-contactNormal.x, -contactNormal.y);
        }

        stone->setNormal(contactNormal);
        if (player->getRole() == ROLE::Pig)
        {
            // 获得player的速度
            stone->m_speed = player->getSpeed().x;
            // TODO: 这里八戒应该换成推石头的动画
            // player->getPlayer()->addPushState();
            this->getScheduler()->schedule(schedule_selector(StoneSprite::pigContactStoneHandler), stone, 0, 0, 0, false);
        }
        else if (player->getRole() == ROLE::Monkey)
        {
            this->getScheduler()->schedule(schedule_selector(StoneSprite::monkeyContactStoneHandler), stone, 0, 0, 0, false);
        }
    }
//    else if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, STONE_TAG, STONE_TAG))
//    {
//        // 处理石头与石头之间的碰撞，不进行任何操作
//        StoneSprite* stoneA = dynamic_cast<StoneSprite*>(spriteA);
//        StoneSprite* stoneB = dynamic_cast<StoneSprite*>(spriteB);
//        this->getScheduler()->schedule(schedule_selector(StoneSprite::stoneContactStoneHandler), stoneA, 0, 0, 0, false);
//        this->getScheduler()->schedule(schedule_selector(StoneSprite::stoneContactStoneHandler), stoneB, 0, 0, 0, false);
//        return true;
//    }

	if (getAnyContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, needNagNormal))
    {
		PhysicsShape * shapeA = contact.getShapeA();
		PhysicsShape * shapeB = contact.getShapeB();

		if(shapeA->getTag() == ATTACKREGION_TAG || shapeB->getTag() == ATTACKREGION_TAG)
		{
			NPCSprite* npc = dynamic_cast<NPCSprite*>(spriteB);
			CCASSERT(npc, "cannot convert Sprite to NPCSprite");
			npc->onHurt();
			return false;
		}
		else
		{
			const PhysicsContactData * data = contact.getContactData();
			PlayerSprite * sprite = dynamic_cast<PlayerSprite*>(spriteA);
			CCASSERT(sprite,"cannot convert Sprite to PlayerSprite at GameScene.cpp");
			Vec2 realNormal = data->normal;

			if (needNagNormal)
				realNormal = Vec2(-realNormal.x, -realNormal.y);

			/*char buffer[256];
			itoa(data->points[0].x, buffer, 10);
			std::string b = buffer;
			char bb[256];
			itoa(data->points[0].y, bb, 10);
			b += ",";
			b += bb;
			b += "\n";
			LOGD(b.c_str(), NULL);*/

			sprite->onCollisionHandle(realNormal);
		}
    }

	return true;
}

void GameScene::onContactSeperate(PhysicsContact& contact)
{
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
    
	if (!sprite1 || !sprite2)
		return;

	Sprite *spriteA, *spriteB;
	bool needNagNormal = false;
	printf("onContactSeperate detected: tagA %d, tagB %d\n",
           sprite1->getTag(), sprite2->getTag());

	if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, ELEVATOR_TAG))
	{
		PlayerSprite * player = dynamic_cast<PlayerSprite*>(spriteA);
		ElevatorSprite * elevator = dynamic_cast<ElevatorSprite*>(spriteB);
		LOGD("Elevator and player Seperate!\n");
		player->SeperateWithElevator();
	}
    else if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, STONE_TAG))
    {
        PlayerSprite* player = dynamic_cast<PlayerSprite*>(spriteA);
        StoneSprite*  stone  = dynamic_cast<StoneSprite*>(spriteB);
		const PhysicsContactData * data = contact.getContactData();
		LOGD("player and stone Seperate!\n");

		if (!data)
			return;

		auto contactNormal = data->normal;
        //stone->setNormal(contactNormal);
        if (player->getRole() == ROLE::Pig) {
            // TODO: 这里八戒恢复成正常的动画
            // player->getPlayer()->removePushState();
            this->getScheduler()->schedule(schedule_selector(StoneSprite::pigSeprateStoneHandler), stone, 0, 0, 0, false);
        }
        else if (player->getRole() == ROLE::Monkey)
        {
            this->getScheduler()->schedule(schedule_selector(StoneSprite::monkeySeprateStoneHandler), stone, 0, 0, 0, false);
        }
    }
    else if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, STONE_TAG, STONE_TAG))
    {
        StoneSprite* stoneA = dynamic_cast<StoneSprite*>(spriteA);
        StoneSprite* stoneB = dynamic_cast<StoneSprite*>(spriteB);
        this->getScheduler()->schedule(schedule_selector(StoneSprite::stoneSeprateStoneHandler), stoneA, 0, 0, 0, false);
        this->getScheduler()->schedule(schedule_selector(StoneSprite::stoneSeprateStoneHandler), stoneB, 0, 0, 0, false);
    }

	if (getAnyContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, needNagNormal))
	{
		PhysicsShape * shapeA = contact.getShapeA();
		PhysicsShape * shapeB = contact.getShapeB();

		if (shapeA->getTag() == ATTACKREGION_TAG || shapeB->getTag() == ATTACKREGION_TAG)
			return;

		const PhysicsContactData * data = contact.getContactData();

		if (!data)
			return;

		PlayerSprite * sprite = dynamic_cast<PlayerSprite*>(spriteA);
		CCASSERT(sprite, "cannot convert Sprite to PlayerSprite at GameScene.cpp");

		Vec2 realNormal = data->normal;

		if (needNagNormal)
			realNormal = Vec2(-realNormal.x, -realNormal.y);

		sprite->onCollisionEnd(realNormal);
	}
}

void GameScene::playerBeAttackedAndUpdateUI(CallBackData* data)
{
	CreatureHpData * hpData = dynamic_cast<CreatureHpData*>(data);
	CCASSERT(hpData, "invaild CreatureHpData");
	m_uiLayer->updateHP(hpData->hp);
}

void GameScene::gameRestart(CallBackData * data)
{
    LOGD("Game is restart");
	cocostudio::ActionManagerEx::destroyInstance();
    auto newGameScene = GameScene::create();
    TransitionScene *transition = TransitionFade::create(1, newGameScene);
    Director::getInstance()->replaceScene(transition);
}

