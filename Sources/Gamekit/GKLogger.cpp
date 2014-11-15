/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        GKLogger.cpp
 *  Created Time:    2014/11/15  14:33:30
 *  Description:
 *  Revision:
 *  License:
 */

#include <cstdarg>

#include "GKLogger.hpp"

GKLogger::GKLogger()
{
    mFilep = NULL;
    mLoglevel = GKLOG_DEBUG;
}

GKLogger::~GKLogger()
{
    if (mFilep) {
        close(mFilep);
    }
    setLogHandler(stdout);
}
 
int GKLogger::setLogFile(const char *filename)
{
    FILE *fp = NULL;
    fp = fopen(filename, "w");
    if (fp) {
        mFilep = fp;
        return 0;
    }
    return -1;
}

int GKLogger::setLogHandler(FILE *filep)
{
    if (filep) {
        mFilep = filep;
    }
    return 0;
}

void GKLogger::log(int loglevel, const char *fmt, ...)
{
    va_list argptr;
    va_start(argptr, fmt);
    sprintf(mFilep, fmt, argptr);
    va_end(argptr);
}

#define GK_GENERATE_LOG_FUNCTION(funcname, loglevel) \
    void GKLogger::funcname(const char *fmt, ...)    \
    {                                                \
        if (mLoglevel >= loglevel) {                 \
            va_list argptr;                          \
            va_start(argptr, fmt);                   \
            log(loglevel, fmt, argptr);              \
            va_end(argptr);                          \
            return 0;                                \
        }                                            \
    }

GK_GENERATE_LOG_FUNCTION(debug2, GKLOG_DEBUG2)
GK_GENERATE_LOG_FUNCTION(debug1, GKLOG_DEBUG1)
GK_GENERATE_LOG_FUNCTION(debug,  GKLOG_DEBUG)
GK_GENERATE_LOG_FUNCTION(info,   GKLOG_INFO)
GK_GENERATE_LOG_FUNCTION(warn,   GKLOG_WARN)
GK_GENERATE_LOG_FUNCTION(error,  GKLOG_ERR)

