#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "../src/EventMgr.h"
#include "../src/ResourceLoader.h"
#include "../src/ResourceMgr.h"

//初始化全局变量*****************************************

//初始化事件管理器单例
EventMgr * EventMgr::m_instance = new EventMgr();
//初始化资源加载单例
ResourceLoader * ResourceLoader::m_instance = new ResourceLoader();
//初始化资源管理类
ResourceMgr * ResourceMgr::m_instance = new ResourceMgr();

//*****************************************************

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}

/******************** tinyxml读取xml文件用法********************

CString appPath = GetAppPath();
string seperator = "\\";
string fullPath = appPath.GetBuffer(0) + seperator + szFileName;
//创建一个XML的文档对象。
TiXmlDocument *myDocument = new TiXmlDocument(fullPath.c_str());
myDocument->LoadFile();
//获得根元素，即Persons。
TiXmlElement *RootElement = myDocument->RootElement();
//输出根元素名称，即输出Persons。
cout << RootElement->Value() << endl;
//获得第一个Person节点。
TiXmlElement *FirstPerson = RootElement->FirstChildElement();
//获得第一个Person的name节点和age节点和ID属性。
TiXmlElement *NameElement = FirstPerson->FirstChildElement();
TiXmlElement *AgeElement = NameElement->NextSiblingElement();
TiXmlAttribute *IDAttribute = FirstPerson->FirstAttribute();
//输出第一个Person的name内容，即周星星；age内容，即；ID属性，即。
cout << NameElement->FirstChild()->Value() << endl;
cout << AgeElement->FirstChild()->Value() << endl;
cout << IDAttribute->Value() << endl;

*/
