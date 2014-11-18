#import <UIKit/UIKit.h>

#include "cocos2d.h"

#include "DiCiData.h"
#include <vector>

using namespace std;
vector<DiCiData*>* diciVector;

int main(int argc, char *argv[]) {

    // 建立全局使用的vector
    diciVector = new vector<DiCiData*>();
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
    [pool release];
    return retVal;
}
