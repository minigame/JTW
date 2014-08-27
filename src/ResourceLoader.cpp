#include "ResourceLoader.h"
#include "Log.h"

#ifdef ANDROID
#include <sys/stat.h>
#endif

USING_NS_CC;

ResourceLoader::ResourceLoader()
{
    m_uiWidget = NULL;
}

ResourceLoader::~ResourceLoader()
{
}

cocos2d::ui::Widget* ResourceLoader::loadUIFromFile(const char * fileName)
{
	return cocostudio::GUIReader::getInstance()->widgetFromJsonFile(fileName);
}

void ResourceLoader::loadArmatureFromFile(const std::string& configFilePath)
{
	cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(configFilePath);
}

ResourceLoader* ResourceLoader::getInstance()
{
	return m_instance;
}

void ResourceLoader::loadAnimationFromFile(const char * fileName)
{
	AnimationCache *animationCache = AnimationCache::getInstance();
	animationCache->addAnimationsWithFile(fileName);
}

cocos2d::Animation* ResourceLoader::getAnimationByName(const char * name)
{
	return AnimationCache::getInstance()->getAnimation(name);
}

bool ResourceLoader::copyAsset(std::string& fileName, std::string& destPath)
{
#ifdef ANDROID

	std::string filePath = FileUtils::getInstance()->fullPathForFilename(fileName);
	unsigned char *bytesData = NULL;
	Data data = FileUtils::getInstance()->getDataFromFile(filePath.c_str());
	bytesData = data.getBytes();
	std::string dest = FileUtils::getInstance()->getWritablePath();

	size_t pos = filePath.find("/");
	std::string temp;

	while (pos != std::string::npos)
	{
		std::string dir = filePath.substr(0, pos);
		temp = filePath.substr(pos + 1, filePath.size());
		dir = dest + dir + "/";
		LOGD(dir.c_str(), NULL);
		mkdir(dir.c_str(),S_IRWXU | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP  );
		pos = temp.find("/");
	}

	//LOGD(dest.c_str(), NULL);
	dest += filePath;
	//LOGD(dest.c_str(), NULL);

	FILE *fp = fopen(dest.c_str(), "w+");

	if (!fp)
	{
		LOGD("cannot open");
		delete[]bytesData;
		bytesData = NULL;
		return false;
	}

	fwrite(bytesData, sizeof(char), data.getSize(), fp);
	fclose(fp);
	destPath = dest;
	return true;

#endif // ANDROID

	return false;
}
