/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        JTWResMng.hpp
 *  Created Time:    2014/11/15  14:01:45
 *  Description:     
 *  Revision:
 *  License:
 */

#ifndef __JTWRESMNG__
#define __JTWRESMNG__ 1

#include "GKConfigMng.hpp"
#include "GKSingleton.hpp"
#include "GKResLoader.hpp"

NS_CC_BEGIN

enum CONFIG_TAG_INDEX {
    CONFIG_TAG_BASIC = 0,
    CONFIG_TAG_PHY,

    CONFIG_TAG_NUM
};

class JTWResMng: public GKConfigMng
{
public:
    JTWResMng();
    ~JTWResMng();

// public interface function
public:
    virtual bool loadConfigFile();
    virtual bool reloadConfigFile();

    GKStrMap *getConfigBasicMap() { return getConfigMapAtIndex(CONFIG_TAG_BASIC); }
    GKStrMap *getConfigPhyMap()   { return getConfigMapAtIndex(CONFIG_TAG_PHY); }

// private helper function
private:
    GKStrMap *getConfigMapAtIndex(int index);

// private members
private:
    GKStrMapVector mConfigMap;
    TiXmlDocument *mXmlDoc;
};

typedef GKSingleton<JTWResMng> JTWResMngSingleton;
#define JTWResMngSig (JTWResMngSingleton::Instance())

NS_CC_END;

#endif
