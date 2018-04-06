//
//  MDInspectorWindow.m
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDInspectorWindow.h"
#import "MDViewMacros.h"
#import "MDControlViewController.h"

@implementation MDInspectorWindow

static MDInspectorWindow *g_window;
static __weak UIView *g_untouchableView;

+ (instancetype)sharedWindow {
    MDViewAssertMainThread();
    return g_window;
}

+ (BOOL)isEnabled {
    MDViewAssertMainThread();
    return g_window != nil;
}

+ (void)enable {
    MDViewAssertMainThread();
    g_window = [[self alloc] initWithFrame:UIScreen.mainScreen.bounds];
    MDControlViewController *vc = [MDControlViewController new];
    UINavigationController *navi = [[UINavigationController alloc] initWithRootViewController:vc];
    navi.navigationBarHidden = YES;
    g_window.rootViewController = navi;
    g_window.windowLevel = UIWindowLevelStatusBar - 1;
    g_window.hidden = NO;
    
    g_untouchableView = vc.view;
}

+ (void)disable {
    g_window.hidden = YES;
    g_window = nil;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
    }
    return self;
}

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event {
    UIView *view = [super hitTest:point withEvent:event];
    if (view != self && view != g_untouchableView) {
        return view;
    }
    return nil;
}


@end
