//
//  MDInspectorWindow.h
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MDInspectorWindow : UIWindow

+ (instancetype)sharedWindow;

+ (BOOL)isEnabled;
+ (void)enable;
+ (void)disable;

@end
