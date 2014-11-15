/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        GKResManager.cpp
 *  Created Time:    2014/11/15  14:01:20
 *  Description:     资源管理器
 *  Revision:
 *  License:
 */

#include "tinyxml/tinyxml.h"

#include "GKLogger.hpp"
#include "GKResManager.hpp"

USING_NS_CC;
USING_NS_STD;

/* -------------------------------------------------- */
/* common interface */

GKResManager::GKResManager()
{

}

GKResManager::~GKResManager()
{

}

/* -------------------------------------------------- */
/* application logic */

GKResManager* GKResManager::getInstance()
{
	return m_instance;
}

bool GKResManager::loadConfigFromXML(TiXmlDocument *xmlDocument, const char *filename)
{
	TiXmlDocument *myDocument = new TiXmlDocument(filePath.c_str());

#if defined(WIN32) || defined(__OSX__)
	if (!myDocument->LoadFile(TIXML_ENCODING_UTF8))
	{
		LOGD("loadfail");
		delete myDocument;
		return false;
	}
#elif defined(ANDROID)
	string destPath;
	string tempPath = filename;
	
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
    return true;
}

bool GKResManager::LoadMapFromXML(TiXmlDocument *xmlDocument, const char *tagname, map &keymap)
{
	TiXmlElement *root = xmlDocument->RootElement();

	if (root == NULL)
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
		string key = child->Attribute("tag");
		string value = child->FirstChild()->Value();
		m_strings[key] = value;

		child = child->NextSiblingElement();
	} while (child);

	delete myDocument;
	myDocument = NULL;
}




bool GKResManager::loadStringFile(const char * fileName)
{
	string filePath = FileUtils::getInstance()->fullPathForFilename(fileName);
	TiXmlDocument *myDocument = new TiXmlDocument(filePath.c_str());

#if defined(WIN32) || defined(__OSX__)
	if (!myDocument->LoadFile(TIXML_ENCODING_UTF8))
	{
		LOGD("loadfail");
		delete myDocument;
		return false;
	}
#elif defined(ANDROID)
	string destPath;
	string tempPath = fileName;
	
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
		string key = child->Attribute("tag");
		string value = child->FirstChild()->Value();
		m_strings[key] = value;

		child = child->NextSiblingElement();
	} while (child);

	delete myDocument;
	myDocument = NULL;
	
	return true;
}

string GKResManager::getString(const string& key)
{
	map<string, string>::iterator it = m_strings.find(key);

	if (it != m_strings.end())
	{
		return it->second;
	}
	else
		return string("");
}

Texture2D* GKResManager::getImage(const string & name)
{
	map<string, string>::iterator it = m_nameMap.find(name);

	if (it == m_nameMap.end())
		return NULL;

	return Director::getInstance()->getTextureCache()->getTextureForKey(it->second);
}

void GKResManager::addImage(const string& fileName, const string& name)
{
	m_nameMap[name] = fileName;
}

void GKResManager::startLoadImage(function<void(void)> callback)
{
	m_imageCount = 0;
	m_loadedCallback = callback;

	map<string, string>::iterator it = m_nameMap.begin();

	for (; it != m_nameMap.end(); ++it)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(it->second, CC_CALLBACK_1(GKResManager::_callback, this));
	}
}

void GKResManager::_callback(cocos2d::Texture2D * texture)
{
	++m_imageCount;

	if (m_imageCount == m_nameMap.size())
	{
		m_loadedCallback();
	}
}
