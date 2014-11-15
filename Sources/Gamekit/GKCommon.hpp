/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        GKCommon.hpp
 *  Created Time:    2014/11/15  11:33:40
 *  Description:     
 *  Revision:
 *  License:
 */

/* -------------------------------------------------- */
/* 常用的简化通用的宏 */

// namespace gamekit {}
#ifdef __cplusplus
    #define NS_GK_BEGIN  namespace gamekit {
    #define NS_GK_END    }
    #define USING_NS_GK  using namespace gamekit
#else
    #define NS_GK_BEGIN 
    #define NS_GK_END 
    #define USING_NS_GK 
#endif 


