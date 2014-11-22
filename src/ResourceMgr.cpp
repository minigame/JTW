#include "ResourceMgr.h"
#include "Log.h"
#include "ResourceLoader.h"

USING_NS_CC;

ResourceMgr::ResourceMgr()
{
}


ResourceMgr::~ResourceMgr()
{
	std::map<std::string, Texture2D*>::iterator it = m_images.begin();

	for (; it != m_images.end(); ++it)
	{
		Texture2D* frame = it->second;
		frame->autorelease();
	}

	m_images.clear();
	m_strings.clear();
}

ResourceMgr* ResourceMgr::getInstance()
{
    return ResourceMgrSig::Instance();
    //return m_instance;
}

bool ResourceMgr::loadStringFile(const char * fileName)
{
	std::string filePath = FileUtils::getInstance()->fullPathForFilename(fileName);
	TiXmlDocument *myDocument = new TiXmlDocument(filePath.c_str());

#if defined(WIN32) or defined(__OSX__) or defined(_ARCH_IOS_)
	if (!myDocument->LoadFile(TIXML_ENCODING_UTF8))
	{
		LOGD("loadfail");
		delete myDocument;
		return false;
	}
#elif defined(ANDROID)
	std::string destPath;
	std::string tempPath = fileName;
	
	if(!ResourceLoader::getInstance()->copyAsset(tempPath,destPath))
	{
		LOGD("loadfail");
		return false;
	}

	myDocument->SetValue(destPath.c_str());

	if (!myDocument->LoadFile(TIXML_ENCODING_UTF8))
	{
		LOGD("loadfail");
		delete myDocument;
		return false;
	}
#endif

	TiXmlElement * root = myDocument->RootElement();

	if (!root)
	{
		LOGD("no root");
		delete myDocument;
		return false;
	}

	m_strings.clear();

	TiXmlElement * child = root->FirstChildElement();

	if (!child)
		return true;

	do 
	{
		std::string key = child->Attribute("tag");
		std::string value = child->FirstChild()->Value();
		m_strings[key] = value;

		child = child->NextSiblingElement();
	} while (child);

	delete myDocument;
	myDocument = NULL;
	
	return true;
}

std::string ResourceMgr::getString(const std::string& key)
{
	std::map<std::string, std::string>::iterator it = m_strings.find(key);

	if (it != m_strings.end())
	{
		return it->second;
	}
	else
		return std::string("");
}

Texture2D* ResourceMgr::getImage(const std::string & name)
{
	std::map<std::string, std::string>::iterator it = m_nameMap.find(name);

	if (it == m_nameMap.end())
		return NULL;

	return Director::getInstance()->getTextureCache()->getTextureForKey(it->second);
}

void ResourceMgr::addImage(const std::string& fileName, const std::string& name)
{
	m_nameMap[name] = fileName;
}

void ResourceMgr::startLoadImage(std::function<void(void)> callback)
{
	m_imageCount = 0;
	m_loadedCallback = callback;

	std::map<std::string, std::string>::iterator it = m_nameMap.begin();

	for (; it != m_nameMap.end(); ++it)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(it->second, CC_CALLBACK_1(ResourceMgr::_callback, this));
	}
}

void ResourceMgr::_callback(cocos2d::Texture2D * texture)
{
	++m_imageCount;

	if (m_imageCount == m_nameMap.size())
	{
		m_loadedCallback();
	}
}
