/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        JTWResMng.cpp
 *  Created Time:    2014/11/15  14:01:20
 *  Description:     资源管理器
 *  Revision:
 *  License:
 */

#include "GKResLoader.hpp"

#include "JTWResMng.hpp"

USING_NS_CC;

/* -------------------------------------------------- */
/* resource mng framework */

JTWResMng::JTWResMng()
{

}

JTWResMng::~JTWResMng()
{

}

/* -------------------------------------------------- */
/* application logic */

bool JTWResMng::loadConfigFile()
{
    bool res;

    #define XML_FILENAME "config/test.xml"
    mXmlDoc = GKResLoader::loadConfigFromXML(XML_FILENAME);

    if (mXmlDoc == NULL) {
        return false;
    }

    // 转换好需要读入的字段
    GKStrStringVector tagnameVec;
    tagnameVec.resize(CONFIG_TAG_NUM);

    tagnameVec[CONFIG_TAG_BASIC] = "basic";
    tagnameVec[CONFIG_TAG_PHY]   = "phy";

    // 准备读入数据
    res = loadMapFromXML(mXmlDoc, tagnameVec, mConfigMap);
    if (res == false) {
        return false;
    }

    return true;
}

bool JTWResMng::reloadConfigFile()
{
    return loadConfigFile();
}

/* -------------------------------------------------- */
/* private helper functions */

GKStrMap *getConfigMapAtIndex(int index)
{
    if (index >= CONFIG_TAG_NUM) {
        return NULL;
    }
    return &mConfigMap[index];
}



