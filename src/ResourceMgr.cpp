#include "ResourceMgr.h"

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

	if (!myDocument->LoadFile(TIXML_ENCODING_UTF8))
	{
		delete myDocument;
		return false;
	}

	TiXmlElement * root = myDocument->RootElement();

	if (!root)
	{
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
