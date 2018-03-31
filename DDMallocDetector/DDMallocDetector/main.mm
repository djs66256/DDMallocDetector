//
//  main.m
//  DDMallocDetector
//
//  Created by hzduanjiashun on 2018/3/30.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import "MemoryDetector.hpp"

int main(int argc, char * argv[]) {
    MD::MemoryDetector::GetInstance()->DetectorAllZones();
    MD::MemoryDetector::GetInstance()->Start();
    
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
