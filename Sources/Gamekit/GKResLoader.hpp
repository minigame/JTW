/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        GKResLoader.cpp
 *  Created Time:    2014/11/15  15:55:49
 *  Description:     资源加载器，以静态成员函数的方式提供
 *  Revision:
 *  License:
 */

#ifndef __GKRESLOADER__
#define __GKRESLOADER__ 1

#include <string>
#include <vector>

#include "cocos2d.h"
#include "tinyxml.h"

#include "GKCommon.hpp"
#include "GKResLoader.hpp"

NS_CC_BEGIN

USING_NS_STD;
using namespace cocos2d::ui;

typedef map<string, string> GKStrMap;
typedef vector<string>      GKStrStringVector;
typedef vector<GKStrMap>    GKStrMapVector;

class GKResLoader
{
// public interface function
public:
    /* @desc: xml file loader */
    static TiXmlDocument * loadConfigFromXML(const char *filename);
    static bool loadMapFromXML(TiXmlDocument *xmlDocument, const char *tagname, GKStrMap &keymap);
    static bool loadMapFromXML(TiXmlDocument *xmlDocument, GKStrStringVector &vec, GKStrMapVector &mapVec);

    /* @desc: ui file loader */
    static Widget* loadUIFromJsonFile(const char *filename);

    /* @desc: Animation file loader */
    static void loadArmatureFromJsonFile(const char *filename);
    static Animation* getAnimationByName(const char *name);

    /* @desc: misc loader */
    static bool copyAssetForAndroid(string &filename, std::string &destPath);
};

NS_CC_END

#endif
