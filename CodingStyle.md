Coding Style for JTW
====================

### Basic rule

* 代码一定以utf-8的方式编码
* 代码以unix的方式来进行linebreaking
* 统一用cpp和hpp作为后缀
* 代码尽量用doxygen生成文档的方式来编写，以便自动生成注释

### File Info

* 每个文件用下面的方式来包含基本信息
  (一般来说一些重要的，类似库的文件描述一栏尽量写的内容多一些)

    /*
     *  Copyright(c), All rights reserved.
     *  Author:          alexzzp@gmail.com
     *  Filename:        TestScene.hpp
     *  Created Time:    2014/11/15  11:03:46
     *  Description:     测试用的scene
     *  Revision:
     *  License:
     */
 

### Files Header 

* 如果是库框架性质的文件，而且本身规模比较大，一定要加入自己的namespace

    namespace gamekit {
    // class defined here
    }

* Header的保护方式, 统一设置为名称的大写

    #ifndef __TESTSCENE__
    #define __TESTSCENE__ 1
    #endif

* 尽量每个头文件对应一个class

* 头文件include的方式

* 在.hpp中尽量少引用头文件(减少编译依赖，加快编译速度)

* 以block的方式引入头文件
 
    #include <string>  先引入std 标准头文件
    #include <vector>
    
    #include "GKSingleton.hpp"  再依次引入库文件
    
    #include "GKResManager.hpp" 最后引入应用相关的头文件

== 函数 ==

* 以doxygen兼容

/*
 * @brief add a shape to body
 * @param shape the shape to be added
 * @param addMassAndMoment if this is true, the shape's mass and moment will be added to body. the default is true
 */
 
* 函数括号不在同一行

void AppDelegate::applicationWillEnterForeground()
{
}

* 判断语句在一行，且if与括号之间要留空格

if () {
    do somethine
}

* 不能使用tab，只能使用4 space

* 每个数字之间一定要有空格

(a + b * 3 - df)

* 如果返回值是指针，用NULL来判断，不要用!preturn, 来强调

if (glview == NULL) {
}

* 如果返回值是bool，用ture false来判断

if (boolval == false) {
}

== class的编程方式 ==

* 基本模板

NS_CC_BEGIN

class TestScene: public Scene
{
public:
    TestScene();
    ~TestScene();

	virtual bool init();
	CREATE_FUNC(TestScene);

// public interface function
public:

// private helper function
private:

// private members
private:
 
};

NS_CC_END

* 成员函数



