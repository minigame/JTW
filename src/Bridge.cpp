#include "Bridge.h"

Bridge::Bridge()
{

}

Bridge::~Bridge()
{

}


void Bridge::initBridgeWithName(char* name)
{
	initWithFile(name);
	m_sprite->setTag(BRIDGE_TAG);
}