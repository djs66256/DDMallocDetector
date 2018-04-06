//
//  MDInspectorIcon.m
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDInspectorIcon.h"

@implementation MDInspectorIcon

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = [UIColor blackColor];
    }
    return self;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [super touchesBegan:touches withEvent:event];
    [self handleTouch:touches.anyObject];
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [super touchesCancelled:touches withEvent:event];
    [self handleTouch:touches.anyObject];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [super touchesEnded:touches withEvent:event];
    [self handleTouch:touches.anyObject];
    [self stickToEdges];
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [super touchesCancelled:touches withEvent:event];
    [self handleTouch:touches.anyObject];
    [self stickToEdges];
}

- (void)handleTouch:(UITouch *)touch {
    CGPoint loc = [touch locationInView:self.superview];
    CGPoint preLoc = [touch previousLocationInView:self.superview];
    
    CGPoint v = CGPointMake(loc.x - preLoc.x, loc.y - preLoc.y);
    CGRect r = self.frame;
    r.origin.x = MAX(0, MIN(self.superview.frame.size.width - self.frame.size.width, r.origin.x + v.x));
    r.origin.y = MAX(0, MIN(self.superview.frame.size.height - self.frame.size.height, r.origin.y + v.y));
    self.frame = r;
}

- (void)stickToEdges {
    CGRect r = self.frame;
    if (self.center.x > self.superview.frame.size.width / 2) {
        // right
        r.origin.x = self.superview.frame.size.width - self.frame.size.width;
    }
    else {
        r.origin.x = 0;
    }
    [UIView animateWithDuration:0.3 animations:^{
        self.frame = r;
    }];
}

@end
