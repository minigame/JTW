#ifndef _CREATURE_H_
#define _CREATURE_H_

/*!
 * \file Creature.h
 * \date 2014/08/10 20:30
 *
 * \author leozzyzheng  lunchunliu  jiaxinli
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 所有生物的基类
 *
 * \note
*/

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"


#define PLAYERTAG 365


using namespace cocos2d;

enum DIR {Left, Right};   //该Creature的方向

class Creature
{
public:
	Creature();
	~Creature();

//成员变量
public:
	//Vec2 m_speed;    //速度，第一个参数是x轴方向速度，第二个参数是Y轴方向速度
	//Vec2 m_acceleration;   //加速度   第一个参数是x轴的加速度，第二个参数是Y轴的加速度（一般是重力）
	/**************************************************生物的精灵图片或动画，player和NPC都包括进来了
	Sprite* m_pSprite;
	Animation* m_pAnimation;
	Animate* m_pAnimate;
	**************************************************/
	Vec2 m_position;     //改生物的位置，这个位置是相对于卷轴的,且是中心位置    ??????????????????
	float m_currentBlood;     //血量
	float m_maxBlood;        //该生物最大血量值
	cocostudio::Armature* m_armature;    //该生物的armature
	cocos2d::PhysicsBody* m_phyBox;
	DIR m_dir;    //该Creature的方向

//构造函数
public:
	//Creature(Vec2 speed, Vec2 acceleration, Vec2 pos, float currentBlood, float maxBlood);
	Creature(float currentBlood, float maxBlood, DIR d);

//成员函数
public:
	virtual void init(){}    //初始化函数，生物的精灵图片或动画的生成写在这
	void setArmature(cocostudio::Armature* armature);    //设置该生物的armature
	void setPhyBody(cocos2d::PhysicsBody* bodyBox);     //设置该生物的物理属性body这个成语变量，不代表该armature和body绑定
	void setTag(int tag);   //给m_armature设置tag
	void setArmatureWithAnimationName(const char* name);   //从ArmatureDataManagerChe里面通过动画名字，给Armature赋值
	void setArmatureWithExportJsonFile(char* filename, char* armatureName);    //通过ExportJson的文件名和动画名字创建Armature给m_armature
	void setAnimationDirByDIR();      //通过该生物的DIR设置动画播放的方向，向右走是正常播放，向左走是反向播放
	void setDir(DIR d);    //设置该生物的行走方向
	void setSpeed(Vec2 v);    //设置该生物的物理速度
	void setPhyByArmatureContentSize();       //根据Armature的形态设置bodybox的大小
	Vec2 getSpeed();
	cocostudio::Armature * getArmature() const;
	//void updatePosition(float dt);     //更新该生物的位置
	//void updateSpeed(float dt);     //更新Y轴的速度
	//void setPosition(Vec2 pos);   //设置生物位置
	//Vec2 calcPosition(float t);      //计算经过一段时间t，该生物的位置

private:
	void bindPhyBody();    //绑定armature和body
};

#endif