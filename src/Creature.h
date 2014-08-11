#pragma once

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

using namespace cocos2d;



class Creature
{
public:
	Creature();
	~Creature();



//成员变量
public:
	Vec2 m_speed;    //速度，第一个参数是x轴方向速度，第二个参数是Y轴方向速度
	Vec2 m_acceleration;   //加速度   第一个参数是x轴的加速度，第二个参数是Y轴的加速度（一般是重力）
	/**************************************************生物的精灵图片或动画，player和NPC都包括进来了
	Sprite* m_pSprite;
	Animation* m_pAnimation;
	Animate* m_pAnimate;
	**************************************************/
	Vec2 m_Position;     //改生物的位置，这个位置是相对于卷轴的,且是中心位置
	float m_CurrentBlood;     //血量
	float m_MaxBlood;        //该生物最大血量值
	/*bool m_bInScene; */   //改生物时候在场景

//构造函数
public:
	Creature(Vec2 speed, Vec2 acceleration, Vec2 pos, float currentBlood, float maxBlood);

//成员函数
public:
	virtual void init(){}    //初始化函数，生物的精灵图片或动画的生成写在这
	void updatePosition(float dt);     //更新该生物的位置
	void updateSpeed(float dt);     //更新Y轴的速度
	void setPosition(Vec2 pos);   //设置生物位置
	Vec2 calcPosition(float t);      //计算经过一段时间t，该生物的位置
};

#endif