#include "Item.h"

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

void Item::setArmatureWithExportJsonFile(char* filename, char* armatureName)
{
	cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(filename);
	m_armature = cocostudio::Armature::create(armatureName);
    //CCASSERT(!m_armature, sprintf("Armature file %s with name %s is not found", filename, armatureName));
    CCASSERT(!m_armature, "Armature file is not found");
}

void Item::setArmature(cocostudio::Armature* armature)
{
	if (m_armature != armature)
		m_armature = armature;
}

cocostudio::Armature * Item::getArmature()
{
	return m_armature;
}
