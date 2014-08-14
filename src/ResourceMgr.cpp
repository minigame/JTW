#include "ResourceMgr.h"
#include "Log.h"
#include "ResourceLoader.h"

USING_NS_CC;

ResourceMgr::ResourceMgr()
{
}


ResourceMgr::~ResourceMgr()
{
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
