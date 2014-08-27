#include "GameScene.h"
#include "Creature.h"
#include "PhyConst.h"
#include "BulletSprite.h"
#include "Tag.h"
#include "GateSprite.h"
#include "Log.h"

USING_NS_CC;

GameScene::GameScene()
{
	m_backRollLayer = new Layer*[MAX_BACKROLLLAYER];
	m_backLayer = NULL;
	m_playerLayer = NULL;
	m_uiLayer = NULL;
	m_obstacleLayer = NULL;
	m_contactListener = NULL;
}

GameScene::~GameScene()
{
    LOGD("game scene is destoryed");
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	if (!this->initWithPhysics())
		return false;

	//getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	this->getPhysicsWorld()->setGravity(Vec2(DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("worldGravity_X")),
		DataConversion::convertStr2float(ResourceMgr::getInstance()->getString("worldGravity_Y"))));

	int i, j;
	bool allCreated = true;
	for (i = 0; i < MAX_BACKROLLLAYER; i++) {
		m_backRollLayer[i] = Layer::create();
		allCreated = allCreated && m_backRollLayer[i];
	}
	m_backLayer = GameBackgroundLayer::create();
    m_backLayer->setTag(BACKGROUND_TAG);

	m_playerLayer = GamePlayerLayer::create();
	m_uiLayer = GameUILayer::create();
	m_obstacleLayer = GameObstacleLayer::create();

	PhysicsWorld* gameWorld = getPhysicsWorld();

	if (!allCreated || !m_backLayer || !m_playerLayer || !m_uiLayer)
		return false;

	for (i = 0; i < MAX_BACKROLLLAYER; i++) {
		addChild(m_backRollLayer[MAX_BACKROLLLAYER - i - 1], i);
	}

	if (!m_backLayer->setTiledMap("map/map_1.tmx"))
	{
		LOGD("Read map failed!\n");
		return false;
	}

	addChild(m_backLayer, i+1);
	addChild(m_obstacleLayer,i+2);
	addChild(m_playerLayer, i+3);
	addChild(m_uiLayer, i+4);
	
	m_backLayer->setPhyWorld(gameWorld);
	m_playerLayer->setPhyWorld(gameWorld);
	m_playerLayer->setBackLayer(m_backLayer);
	m_playerLayer->setObstacleLayer(m_obstacleLayer);
	m_playerLayer->setBackRollLayer(m_backRollLayer);
	m_uiLayer->setDelegator(m_playerLayer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto edgeSp = Sprite::create();
	auto body = PhysicsBody::createEdgeBox(visibleSize, MY_PHYSICSBODY_MATERIAL_DEFAULT, 3);

	body->setCategoryBitmask(GROUND_CATEGORYBITMASK);
	body->setContactTestBitmask(GROUND_CONTACTTESTBITMASK);
	body->setCollisionBitmask(GROUND_COLLISIONBITMASK);
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(body);
    this->addChild(edgeSp);
    edgeSp->setTag(EDGE_TAG);

	for (i = 0; i < MAX_BACKROLLLAYER; i++)
	{
		int offset = 0;
		for (j = 0; j < MAP_SIZE[0][i]; j++)
		{
			char path[100];
			sprintf(path, "map/map_1_%d_%d.png", i + 1, j + 1);
			auto BackRollSplit = Sprite::createWithSpriteFrame(ResourceMgr::getInstance()->getImage(path));
			BackRollSplit->setPosition(Point(offset + BackRollSplit->getContentSize().width / 2, BackRollSplit->getContentSize().height / 2));
			offset += BackRollSplit->getContentSize().width;
			m_backRollLayer[i]->addChild(BackRollSplit);
		}
	}

	m_contactListener = EventListenerPhysicsContact::create();
	m_contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	m_contactListener->onContactSeperate = CC_CALLBACK_1(GameScene::onContactSeperate, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_contactListener, this);


	CallBackMgr::getInstance()->registerFunction(PLAYER_BE_ATTACKED, "playerBeAttacked", MY_CALL_BACK_1(GameScene::playerBeAttackedAndUpdateUI,this));

	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	//鈥欌€氣垙藛鈥濃€撯埆鈥光垈鈥÷灯掆垜惟鈭懧?
	//getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_contactListener, this);
}

void GameScene::onExit()
{
	Scene::onExit();
	getEventDispatcher()->removeAllEventListeners();
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

	if (!sprite1 || !sprite2)
		return false;

    Sprite *spriteA, *spriteB;
	bool needNagNormal = false;
    printf("contact detected: tagA %d, tagB %d\n", sprite1->getTag(), sprite2->getTag());

    // 处理item与边沿以及地面碰撞事件
    if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, ITEM_TAG, EDGE_TAG))
    {
        BulletSprite * aBulletSprite = dynamic_cast<BulletSprite*>(spriteA);
		CCASSERT(aBulletSprite,"invaild bullet");
        aBulletSprite->contactHandler();
		return true;//必须return，对象已经销毁了
	}
	else if(getContactObject(&spriteA, &spriteB, sprite1, sprite2, ITEM_TAG, BACKGROUND_TAG))
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


				CallBackMgr::getInstance()->tigger(BRIDGE_ROTATE, NULL);
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
		player->onContactWithElevator(elevator);
	}
	else if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, GATE_TAG))
	{
		/*PlayerSprite* player = dynamic_cast<PlayerSprite*>(spriteA);
		GateSprite* gate = dynamic_cast<GateSprite*>(spriteB);*/


		CallBackMgr::getInstance()->tigger(PLAYER_BE_ATTACKED, NULL);
		/*player->beAttacked();
		updateUI();*/

		////调用triger();
	
	}

    
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


void GameScene::updateUI()
{
	//if()
	int currentBlood = m_playerLayer->getPlayerSprite()->getPlayer()->getBlood();
	//if(currentBlood == 0)   //没有血了
	m_uiLayer->updateHP(currentBlood);
}

void GameScene::onContactSeperate(PhysicsContact& contact)
{
	auto sprite1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto sprite2 = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (!sprite1 || !sprite2)
		return;

	Sprite *spriteA, *spriteB;
	bool needNagNormal = false;
	printf("onContactSeperate detected: tagA %d, tagB %d\n", sprite1->getTag(), sprite2->getTag());

	if (getContactObject(&spriteA, &spriteB, sprite1, sprite2, PLAYER_TAG, ELEVATOR_TAG))
	{
		PlayerSprite * player = dynamic_cast<PlayerSprite*>(spriteA);
		ElevatorSprite * elevator = dynamic_cast<ElevatorSprite*>(spriteB);
		LOGD("Elevator and player Seperate!\n");
		player->SeperateWithElevator();
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
	m_playerLayer->getPlayerSprite()->beAttacked();
	updateUI();
}
