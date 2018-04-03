//
//  main.m
//  DDMallocDetector
//
//  Created by hzduanjiashun on 2018/3/30.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import "MallocDetector.h"

int main(int argc, char * argv[]) {
    malloc_detector_show_inspector();
    malloc_detector_attach_zone(YES);
    malloc_detector_start();
    
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
