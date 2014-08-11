#include "Creature.h"

Creature::Creature()
{
	m_speed = Vec2(0.0f, 0.0f);
	m_acceleration = Vec2(0.0f, 0.0f);
	m_Position = Vec2(0.0f, 0.0f);
	m_CurrentBlood = 0.0f;
	m_MaxBlood = 0.0f;
}

Creature::~Creature()
{
	//这块是不是要释放精灵动画
}

Creature::Creature(Vec2 speed, Vec2 acceleration, Vec2 pos, float currentBlood, float maxBlood)
{
	m_speed = speed;
	m_acceleration = acceleration;
	m_Position = pos;
	//m_vPosition = pos;
	if(currentBlood >= 0.0f)
		m_CurrentBlood = currentBlood;
	else
		m_CurrentBlood = 0.0f;

	if(maxBlood >= 0.0f)
		m_MaxBlood = maxBlood;
	else
		m_MaxBlood = 0.0f;

	//m_bInScene = bs;
}

void Creature::updatePosition(float dt)
{
	///////////////////这块是不是要判断位置的上下限；
	//m_vPosition = m_vPosition + m_vXSpeed*dt + m_vYSpeed*dt + Vec2(0.0f, 0.5f*dt*dt);
	m_Position = calcPosition(dt);
}

void Creature::updateSpeed(float dt)
{
	//m_vYSpeed = m_vYSpeed + Vec2(0, m_fGravityAcceleration*dt); 
	m_speed = m_speed + m_acceleration*dt;
}


void Creature::setPosition(Vec2 pos)
{
	if(pos != m_Position)
	{
		m_Position = pos;
	}
}

Vec2 Creature::calcPosition(float t)
{
	Vec2 pos;
	pos = m_Position + m_speed*t + 0.5f*m_acceleration*t*t;
	return pos;
}
