/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        GKConfigMng.hpp
 *  Created Time:    2014/11/15  16:47:28
 *  Description:     定义一个配置文件的接口，每个游戏应该都实现这个
 *                   这个接口以便能够在游戏进行中更新配置文件
 *  Revision:
 *  License:
 */

class GKConfigMng
{
public:
    GKConfigMng();
    virtual ~GKConfigMng();

// public interface function
public:
    virtual bool loadConfigFile()   = 0;
    virtual bool reloadConfigFile() = 0;

};
