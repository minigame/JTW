#include "ResourceMgr.h"
#include "Log.h"
#include "ResourceLoader.h"

USING_NS_CC;

ResourceMgr::ResourceMgr()
{
}


ResourceMgr::~ResourceMgr()
{
	std::map<std::string, SpriteFrame*>::iterator it = m_images.begin();

	for (; it != m_images.end(); ++it)
	{
		SpriteFrame* frame = it->second;
		frame->autorelease();
	}

	m_images.clear();
	m_strings.clear();
}

ResourceMgr* ResourceMgr::getInstance()
{
	return m_instance;
}

bool ResourceMgr::loadStringFile(const char * fileName)
{
	std::string filePath = FileUtils::getInstance()->fullPathForFilename(fileName);
    LOGD(filePath);
	TiXmlDocument *myDocument = new TiXmlDocument(filePath.c_str());

	const char* path = filePath.c_str();
	LOGD(path,NULL);

#if defined(WIN32) || defined(__OSX__)
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

//void ResourceMgr::__addImage(Texture2D * texture, const std::string originPath)
//{
//	Size size = texture->getContentSize();
//	auto frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, size.width, size.height));
//
//	std::map<std::string, std::string>::iterator it = m_nameMap.find(originPath);
//
//	CCASSERT(it != m_nameMap.end(), "cannot load imag Async caused by cannot find originPath!");
//
//	std::string name = m_nameMap[originPath];
//	this->m_images[name] = frame;
//	m_nameMap.erase(it);
//	//Use std::map need retain 
//	frame->retain();
//}
//
//void ResourceMgr::addImage(const std::string & fileName, const std::string & name)
//{
//	std::map<std::string, SpriteFrame*>::const_iterator it = m_images.find(name);
//
//	if (it != m_images.cend())
//	{
//		return;
//	}
//
//	//must need it
//	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
//
//	m_nameMap[fullPath] = name;
//	Director::getInstance()->getTextureCache()->addImageAsync(fileName, CC_CALLBACK_2(ResourceMgr::__addImage, this));
//}

SpriteFrame* ResourceMgr::getImage(const std::string & name)
{
	std::map<std::string, SpriteFrame*>::iterator it = m_images.find(name);

	if (it != m_images.end())
	{
		SpriteFrame * frame = it->second;
		frame->autorelease();
		return frame;
	}
	else
		return NULL;
}

void ResourceMgr::addImage(Texture2D* texture, const std::string& name)
{
	Size size = texture->getContentSize();
	auto frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, size.width, size.height));

	std::map<std::string, SpriteFrame*>::iterator it = m_images.find(name);

	if (it != m_images.end())
		return;

	m_images[name] = frame;

	//Use std::map need retain 
	frame->retain();
}
