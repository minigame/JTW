/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        GKLogger.hpp
 *  Created Time:    2014/11/15  14:31:15
 *  Description:     日志记录
 *  Revision:
 *  License:
 */

#ifndef __GKLOGGER__
#define __GKLOGGER__ 1

#include <cstdio>

#include "GKSingleton.hpp"

enum GKLOG_LEVEL
{
    GKLOG_DEBUG2 = 1,
    GKLOG_DEBUG1 = 2,
    GKLOG_DEBUG  = 3,
    GKLOG_INFO   = 4,
    GKLOG_WARN   = 5,
    GKLOG_ERR    = 6,

    GKLOG_NONE,
};

class GKLogger
{
public:
    GKLogger();
    ~GKLogger();

// public interface function
public:
    // TODO: add socket support
    void setLogFile(const char *filename);
    void setLogHandler(FILE *filep);
    void setLogLevel(int loglevel) { mLoglevel = loglevel };

    void debug();
    void info();
    void warn();
    void error();

// private helper function
private:
    void log(int loglevel, const char *fmt, ...);

// private members
private:
    FILE *mFilep;
    int mLoglevel;
};

typedef GKSingleton<GKLogger> GKLoggerSingleton;
#define GKLog (GKLoggerSingleton::Instance())

#endif
