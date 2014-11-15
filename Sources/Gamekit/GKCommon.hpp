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

// namespace std {}
#ifdef __cplusplus
    #define NS_STD_BEGIN  namespace std {
    #define NS_STD_END    }
    #define USING_NS_STD  using namespace std
#else
    #define NS_STD_BEGIN 
    #define NS_STD_END 
    #define USING_NS_STD 
#endif 

// namespace cocostudio {}
#ifdef __cplusplus
    #define NS_CCSTUDIO_BEGIN  namespace cocostudio {
    #define NS_CCSTUDIO_END    }
    #define USING_NS_CCSTUDIO  using namespace cocostudio
#else
    #define NS_CCSTUDIO_BEGIN 
    #define NS_CCSTUDIO_END 
    #define USING_NS_CCSTUDIO 
#endif 
