#include "Item.h"
#include "ResourceLoader.h"

using namespace cocostudio;
USING_NS_CC;

Item::Item()
{
}

Item::~Item()
{
    if (m_armature) {
        // cleanup Armature
    }
    if (m_phyBox) {
        // cleanup m_phyBox
    }
}

void Item::init()
{
    m_position.x = 0.0f;
    m_position.y = 0.0f;
    m_phyBox = NULL;
    m_armature = NULL;
}

void Item::setArmatureWithExportJsonFile(const char* armatureName)
{
 	m_armature = Armature::create(armatureName);
    CCASSERT(m_armature, "Armature file is not found");
}

void Item::setArmature(cocostudio::Armature* armature)
{
	if (m_armature != armature)
		m_armature = armature;
}

cocostudio::Armature * Item::getItemArmature()
{
	return m_armature;
}
