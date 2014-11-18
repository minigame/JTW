#import <UIKit/UIKit.h>

#include "cocos2d.h"
// #include "AppDelegate.h"
//#include "Instance.h"

//#include "ResourceLoader.h"
//#include "ResourceMgr.h"
//#include "CallBackMgr.h"

#include "DiCiData.h"
#include <vector>

using namespace std;
vector<DiCiData*>* diciVector;

int main(int argc, char *argv[]) {
//    //≥ı ºªØ◊ ‘¥º”‘ÿµ•¿˝
//    ResourceLoader * ResourceLoader::m_instance = new ResourceLoader();
//    //≥ı ºªØ◊ ‘¥π‹¿Ì¿‡
//    ResourceMgr * ResourceMgr::m_instance = new ResourceMgr();
//    
//    CallBackMgr * CallBackMgr::m_instance = new CallBackMgr();

    diciVector = new vector<DiCiData*>();
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
    [pool release];
    return retVal;
}
