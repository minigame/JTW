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
#include "cocostudio/CocoStudio.h"
#include "EventDef.h"

using namespace cocos2d;

enum DIR {Left, Right, NoMoveLeft, NoMoveRight};   //��Creature�ķ���

const PhysicsMaterial MY_PHYSICSBODY_MATERIAL_DEFAULT(0.0f, 0.0f, 0.0f);

class Creature 
{
public:
	Creature();
	~Creature();

//��Ա����
public:
	//Vec2 m_speed;    //�ٶȣ���һ��������x�᷽���ٶȣ��ڶ���������Y�᷽���ٶ�
	//Vec2 m_acceleration;   //���ٶ�   ��һ��������x��ļ��ٶȣ��ڶ���������Y��ļ��ٶȣ�һ����������
	/**************************************************����ľ���ͼƬ�򶯻���player��NPC������������
	Sprite* m_pSprite;
	Animation* m_pAnimation;
	Animate* m_pAnimate;
	**************************************************/
	Vec2 m_position;     //�������λ�ã����λ��������ھ����,��������λ��    ??????????????????
	float m_currentBlood;     //Ѫ��
	float m_maxBlood;        //���������Ѫ��ֵ
	cocostudio::Armature* m_armature;    //�������armature
	cocos2d::PhysicsBody* m_phyBox;
	DIR m_dir;    //��Creature�ķ���

//���캯��
public:
	//Creature(Vec2 speed, Vec2 acceleration, Vec2 pos, float currentBlood, float maxBlood);
	Creature(float currentBlood, float maxBlood, DIR d);

//��Ա����
public:
	virtual void init(){}    //��ʼ������������ľ���ͼƬ�򶯻�������д����
	void setArmature(cocostudio::Armature* armature);    //���ø������armature
	//void setPhyBody(cocos2d::PhysicsBody* bodyBox);     //���ø��������������body�������������������armature��body��
	void setTag(int tag);   //��m_armature����tag
	bool setArmatureWithAnimationName(const char* name);   //��ArmatureDataManagerChe����ͨ���������֣���Armature��ֵ
	void setArmatureWithExportJsonFile(char* filename, char* armatureName);    //ͨ��ExportJson���ļ����Ͷ������ִ���Armature��m_armature
	void setAnimationDirByDIR();      //ͨ���������DIR���ö������ŵķ������������������ţ��������Ƿ��򲥷�
	void setDir(DIR d);    //���ø���������߷���
	DIR  getDir() const;
	void setSpeed(Vec2 v);    //���ø�����������ٶ�
	Vec2 getSpeed();
	cocostudio::Armature * getArmature() const;
	//void updatePosition(float dt);     //���¸������λ��
	//void updateSpeed(float dt);     //����Y����ٶ�
	//void setPosition(Vec2 pos);   //��������λ��
	//Vec2 calcPosition(float t);      //���㾭��һ��ʱ��t���������λ��
	void bindPhyBody(Node* parent);    //��armature��body
private:
	void setPhyByArmatureContentSize(bool fourceChange);       //����Armature����̬����bodybox�Ĵ�С
};

#endif