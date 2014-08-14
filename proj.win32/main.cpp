#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "../src/Instance.h"

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

/******************** tinyxml��ȡxml�ļ��÷�********************

CString appPath = GetAppPath();
string seperator = "\\";
string fullPath = appPath.GetBuffer(0) + seperator + szFileName;
//����һ��XML���ĵ�����
TiXmlDocument *myDocument = new TiXmlDocument(fullPath.c_str());
myDocument->LoadFile();
//��ø�Ԫ�أ���Persons��
TiXmlElement *RootElement = myDocument->RootElement();
//�����Ԫ�����ƣ������Persons��
cout << RootElement->Value() << endl;
//��õ�һ��Person�ڵ㡣
TiXmlElement *FirstPerson = RootElement->FirstChildElement();
//��õ�һ��Person��name�ڵ��age�ڵ��ID���ԡ�
TiXmlElement *NameElement = FirstPerson->FirstChildElement();
TiXmlElement *AgeElement = NameElement->NextSiblingElement();
TiXmlAttribute *IDAttribute = FirstPerson->FirstAttribute();
//�����һ��Person��name���ݣ��������ǣ�age���ݣ�����ID���ԣ�����
cout << NameElement->FirstChild()->Value() << endl;
cout << AgeElement->FirstChild()->Value() << endl;
cout << IDAttribute->Value() << endl;

*/
