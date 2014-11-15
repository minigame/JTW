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

class JTWResMng: public GKConfigMng
{
public:
    JTWResMng();
    ~JTWResMng();

// public interface function
public:
    virtual bool loadConfigFile();
    virtual bool reloadConfigFile();

// private helper function
private:

// private members
private:
    GKStrMapVector mConfigMap;
    TiXmlDocument *mXmlDoc;
};

typedef GKSingleton<JTWResMng> JTWResMngSingleton;

#endif
