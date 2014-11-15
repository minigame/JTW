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
    #define XML_FILENAME "config/test.xml"
    mXmlDoc = GKResLoader::loadConfigFromXML(XML_FILENAME);

    if (mXmlDoc == NULL) {
        GKResLoader
    }
    


    GKStrStringVector tagnameVec;

    // 先加入所需要的tag
    tagnameVec.push_back("basic");
    tagnameVec.push_back("phy");
 

    GKStrStringVector mConfigVec;
    
}

bool JTWResMng::reloadConfigFile()
{
    return loadConfigFile();
}
