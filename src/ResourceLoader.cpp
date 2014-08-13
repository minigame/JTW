#include "ResourceLoader.h"


ResourceLoader::ResourceLoader()
{
}


ResourceLoader::~ResourceLoader()
{
}

cocos2d::ui::Widget* ResourceLoader::loadUIFromFile(const char * fileName)
{
	return cocostudio::GUIReader::getInstance()->widgetFromJsonFile(fileName);
}

cocostudio::Armature* ResourceLoader::loadAnimationFromFile(const std::string& fileName, int tag)
{
	cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(fileName);

	std::string basefilePath = fileName;
	size_t pos = basefilePath.find_last_of("/");

	if (pos != std::string::npos)
	{
		basefilePath = basefilePath.substr(0, pos + 1);
	}
	else
	{
		basefilePath = "";
	}

	cocostudio::Armature* armature = cocostudio::Armature::create(basefilePath);
	armature->setTag(tag);
	return armature;
}

ResourceLoader* ResourceLoader::getInstance()
{
	return m_instance;
}
