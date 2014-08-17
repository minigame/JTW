#include "GamePlayerLayer.h"

GamePlayerLayer::GamePlayerLayer()
{
	m_world = NULL;
};

GamePlayerLayer::~GamePlayerLayer(){};

bool GamePlayerLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//get the origin point of the X-Y axis, and the visiable size of the screen
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	//Sprite *background;
	//background = Sprite::create("splash.png");
	//
	//background->setAnchorPoint(Point::ZERO);
	//background->setPosition(Point::ZERO);
	//this->addChild(background);

	//create a bird and set the position in the center of the screen
	m_playerSprite = PlayerSprite::create();
	m_playerSprite->setPosition(Point(origin.x + visiableSize.width / 2, origin.y + visiableSize.height * 3 / 5 - 10));
	this->addChild(m_playerSprite);

	return true;
}

void GamePlayerLayer::onTouch()
{
	
}

void GamePlayerLayer::onLeftButton()
{
	m_playerSprite->walk(false);
}

void GamePlayerLayer::onRightButton()
{
	m_playerSprite->walk(true);
}

void GamePlayerLayer::onActionButton()
{

}

void GamePlayerLayer::onJumpButton()
{
	m_playerSprite->jump();
}

void GamePlayerLayer::onNoAction()
{
	m_playerSprite->noAction();
}

void GamePlayerLayer::setPhyWorld(PhysicsWorld* world)
{
	m_world = world;
}


