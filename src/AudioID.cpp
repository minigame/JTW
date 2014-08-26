#include "AudioID.h"

AudioID::AudioID()
{
}


AudioID::~AudioID()
{
	
}

AudioID* AudioID::getInstance()
{
	return m_instance;
}