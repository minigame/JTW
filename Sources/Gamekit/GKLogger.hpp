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
    int setLogFile(const char *filename);
    int setLogHandler(FILE *filep);
    void setLogLevel(int loglevel) { mLoglevel = loglevel; }

    void debug2(const char *fmt, ...);
    void debug1(const char *fmt, ...);
    void debug(const char *fmt, ...);
    void info(const char *fmt, ...);
    void warn(const char *fmt, ...);
    void error(const char *fmt, ...);

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
