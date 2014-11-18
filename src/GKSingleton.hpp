/*
 *  Copyright(c), All rights reserved.
 *  Author:          alexzzp@gmail.com
 *  Filename:        GKSingleton.hpp
 *  Created Time:    2014/11/15  11:33:01
 *  Description:     封装对class进行单例，若需要单例化一个class，则在class的定义
 *                   文件后面加一个typedef，定义一个带Singleton后缀的class，之后用这个来引用
 *                   typedef CSingleton<ClassName> ClassNameSingleton;
 *  Revision:
 *  License:
 */

#ifndef __GKSINGLETON__
#define __GKSINGLETON__ 1

template <class TYPE>
class GKSingleton
{
public:
    GKSingleton()  {}
    ~GKSingleton() {}
    static TYPE* Instance(void)
    {
        if(mSingleton == NULL)
        {
            mSingleton = new GKSingleton;
        }
        return &mSingleton->mInstance;
    }

    static void Destroy()
    {
        delete mSingleton;
        mSingleton = 0;
    }

protected:
    TYPE mInstance;
    static GKSingleton<TYPE>* mSingleton;
};

template <class TYPE>
GKSingleton<TYPE>* GKSingleton<TYPE>::mSingleton = NULL;

#endif
