#include "GamePlayerLayer.h"

GamePlayerLayer::GamePlayerLayer(){};

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
	m_player = PlayerSprite::create();
	m_player->setPosition(Point(origin.x + visiableSize.width / 2, origin.y + visiableSize.height * 3 / 5 - 10));
	this->addChild(m_player);

	return true;
}

void GamePlayerLayer::onTouch()
{
	if (m_player->getState())
		m_player->stop();
	else
		m_player->walk();
}

void GamePlayerLayer::onLeftButton()
{

}

void GamePlayerLayer::onRightButton()
{

}

void GamePlayerLayer::onActionButton()
{

}

void GamePlayerLayer::onJumpButton()
{

}
