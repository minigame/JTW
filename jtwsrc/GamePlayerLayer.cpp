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
	
	Sprite *background;
	background = Sprite::create("splash.png");
	
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	this->addChild(background);

	//create a bird and set the position in the center of the screen
	this->bird = Sprite::create("CloseSelected.png");
	//this->bird->createBird();
	//this->bird->setTag(BIRD_SPRITE_TAG);
	this->bird->setPosition(Point(origin.x + visiableSize.width / 2,origin.y + visiableSize.height*3/5 - 10));
	//this->bird->idle();
	this->addChild(this->bird);

	return true;
}

void GamePlayerLayer::onTouch(){
	this->bird->fly();
}