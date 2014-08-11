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
 * TODO: ��������Ļ���
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



//��Ա����
public:
	Vec2 m_speed;    //�ٶȣ���һ��������x�᷽���ٶȣ��ڶ���������Y�᷽���ٶ�
	Vec2 m_acceleration;   //���ٶ�   ��һ��������x��ļ��ٶȣ��ڶ���������Y��ļ��ٶȣ�һ����������
	/**************************************************����ľ���ͼƬ�򶯻���player��NPC������������
	Sprite* m_pSprite;
	Animation* m_pAnimation;
	Animate* m_pAnimate;
	**************************************************/
	Vec2 m_Position;     //�������λ�ã����λ��������ھ����,��������λ��
	float m_CurrentBlood;     //Ѫ��
	float m_MaxBlood;        //���������Ѫ��ֵ
	/*bool m_bInScene; */   //������ʱ���ڳ���

//���캯��
public:
	Creature(Vec2 speed, Vec2 acceleration, Vec2 pos, float currentBlood, float maxBlood);

//��Ա����
public:
	virtual void init(){}    //��ʼ������������ľ���ͼƬ�򶯻�������д����
	void updatePosition(float dt);     //���¸������λ��
	void updateSpeed(float dt);     //����Y����ٶ�
	void setPosition(Vec2 pos);   //��������λ��
	Vec2 calcPosition(float t);      //���㾭��һ��ʱ��t���������λ��
};

#endif