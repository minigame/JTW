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
		frame->release();
	}

	m_images.clear();
}

ResourceMgr* ResourceMgr::getInstance()
{
	return m_instance;
}

bool ResourceMgr::loadStringFile(const char * fileName)
{
	std::string filePath = FileUtils::getInstance()->fullPathForFilename(fileName);
	TiXmlDocument *myDocument = new TiXmlDocument(filePath.c_str());

	const char* path = filePath.c_str();
	LOGD(path,NULL);

#ifdef WIN32
	if (!myDocument->LoadFile(TIXML_ENCODING_UTF8))
	{
		LOGD("loadfail");
		delete myDocument;
		return false;
	}
#else
	#ifdef ANDROID
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

bool ResourceMgr::addImage(Texture2D * texture, const std::string & name)
{
	std::map<std::string, SpriteFrame*>::const_iterator it = m_images.find(name);

	if (it != m_images.cend())
	{
		return false;
	}

	Size size = texture->getContentSize();
	auto frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, size.width, size.height));
	this->m_images[name] = frame;
	//Use std::map need retain 
	frame->retain();
	return true;
}

bool ResourceMgr::addImage(const std::string & fileName, const std::string & name)
{
	std::string filePath;
#if defined(ANDROID)
	if(!ResourceLoader::copyAsset(fileName,filePath))
		return false;
#else
	filePath = FileUtils::getInstance()->fullPathForFilename(fileName);
#endif
	Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(filePath);

	if (!texture)
		return false;

	return addImage(texture, name);
}

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
