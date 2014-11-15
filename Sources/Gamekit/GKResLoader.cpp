/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        GKResLoader.cpp
 *  Created Time:    2014/11/15  15:55:49
 *  Description:     资源加载器
 *  Revision:
 *  License:
 */

#ifdef _ARCH_ANDROID_
    #include <sys/stat.h>
#endif

#include "cocos2d.h"
#include "tinyxml/tinyxml.h"

#include "GKLogger.hpp"
#include "GKResLoader.hpp"

USING_NS_CC;
USING_NS_CCSTUDIO;
using namespace cocos2d::ui;

USING_NS_STD;

/* -------------------------------------------------- */
/* xml file loader */

TiXmlDocument * GKResLoader::loadConfigFromXML(const char *filename)
{
    // TODO: 这里能否去掉对cocos2dx的依赖?
	string filePath = FileUtils::getInstance()->fullPathForFilename(Filename);
	TiXmlDocument *xmlDocument = new TiXmlDocument(filePath.c_str());

#if defined(_ARCH_WIN32_) || defined(_ARCH_OSX_)
	if (xmlDocument->LoadFile(TIXML_ENCODING_UTF8) == false) {
		GKLog->error("loadfail for file %s\n", filename);
		delete xmlDocument;
		return NULL;
	}
#elif defined(_ARCH_ANDROID_)
	string destPath;
	string tempPath = filename;
	if(ResourceLoader::getInstance()->copyAssetForAndroid(tempPath, destPath) == false)
	{
        GKLog->error("load file fail\n");
		return false;
	}

	xmlDocument->SetValue(destPath.c_str());

	if (xmlDocument->LoadFile(TIXML_ENCODING_UTF8) == false)
	{
		GKLog->error("loadfail for file %s\n", filename);
		delete xmlDocument;
		return false;
	}
#endif
    return xmlDocument;
}

bool GKResLoader::loadMapFromXML(TiXmlDocument *xmlDocument, const char *tagname, GKStrMap &keymap)
{
	TiXmlElement *root = xmlDocument->RootElement();

	if (root == NULL)
	{
		GKLog->error("no root for xml file\n");
		return false;
	}

	keymap.clear();
	TiXmlElement *child = root->FirstChildElement();
	if (child == NULL) {
		return true;
    }
    // iteratre the xml tree
	do 
	{
        string key   = child->Attribute(tagname);
		string value = child->FirstChild()->Value();
		keymap[key]  = value;

		child = child->NextSiblingElement();
	} while (child);

    return true;
}

bool GKResLoader::loadMapFromXML(TiXmlDocument *xmlDocument, GKStrStringVector &vec, GKStrMapVector &mapVec)
{
    int len = vec.size();
    for (int i = 0; i < len; i++) {
        bool res;
        res = LoadMapFromXML(xmlDocument, vec[i], mapVec[i]);
        if (res == false) {
            GKLog->error("parse tagname %s fail\n", vec[i]);
            return false;
        }
    }
    return true;
}

/* -------------------------------------------------- */
/* UI loader */

Widget* GKResLoader::loadUIFromJsonFile(const char *filename)
{
	return GUIReader::getInstance()->widgetFromJsonFile(filename);
}

/* -------------------------------------------------- */
/* Animation loader */

void GKResLoader::loadArmatureFromJsonFile(const char *filename)
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo(filename);
}

Animation* GKResLoader::getAnimationByName(const char *name)
{
	return AnimationCache::getInstance()->getAnimation(name);
}

/* -------------------------------------------------- */
/* misc function */

bool GKResLoader::copyAssetForAndroid(string &filename, string &destPath)
{
	string filePath = FileUtils::getInstance()->fullPathForFilename(filename);
	unsigned char *bytesData = NULL;
	Data data = FileUtils::getInstance()->getDataFromFile(filePath.c_str());
	bytesData = data.getBytes();
	string dest = FileUtils::getInstance()->getWritablePath();

	size_t pos = filePath.find("/");
	string temp;

	while (pos != string::npos)
	{
		string dir = filePath.substr(0, pos);
		temp = filePath.substr(pos + 1, filePath.size());
		dir = dest + dir + "/";
		mkdir(dir.c_str(), S_IRWXU | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
		pos = temp.find("/");
	}

	dest += filePath;
	FILE *fp = fopen(dest.c_str(), "w+");

	if (!fp)
	{
        GKLog->error("can not open file\n");
		delete [] bytesData;
		bytesData = NULL;
		return false;
	}

	fwrite(bytesData, sizeof(char), data.getSize(), fp);
	fclose(fp);
	destPath = dest;
	return true;
}

