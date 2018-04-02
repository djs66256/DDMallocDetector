//
//  AxisLayer.cpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/30.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include "AxisLayer.hpp"
#include "CanvasLayer.h"
#include <UIKit/UIKit.h>

namespace MD {
    
    static UIColor* UIColorFrom(Color& c) {
        return [UIColor colorWithRed:c.red() green:c.green() blue:c.blue() alpha:c.alpha()];
    }
    
    void XAxisLayer::Draw() {
//        getAnchors()->Prepare();
        auto ctx = canvas()->context();
        auto r = absoluteFrame();
        
        CGContextSaveGState(ctx);
        
        // stroke line
        CGContextMoveToPoint(ctx, r.left(), r.bottom());
        CGContextAddLineToPoint(ctx, r.right() + triangleHeight(), r.bottom());
        
        CGContextSetStrokeColor(ctx, color());
        CGContextStrokePath(ctx);
        
        if (anchors() && anchors()->count()) {
            // stroke anchor
            for (int i = 0; i < anchors()->count(); ++i) {
                Float x = r.left() + r.width() * anchors()->positionAt(i);
                
                CGContextMoveToPoint(ctx, x, r.bottom());
                CGContextAddLineToPoint(ctx, x, r.bottom() + 3);
                CGContextStrokePath(ctx);
                
                NSString *text = nullptr;
                std::string str = anchors()->nameAt(i);
                if (str.size()) {
                    text = [NSString stringWithCString:str.c_str() encoding:NSUTF8StringEncoding];
                }
                else {
                    text = @"";
                }
                
                [text drawInRect:CGRectMake(x - 8, r.bottom() + 8, 20*2, 14)
                  withAttributes:@{
                                   NSForegroundColorAttributeName: UIColorFrom(textColor()),
                                   NSFontAttributeName: [UIFont systemFontOfSize:12],
//                                   NSattname: @(NSTextAlignmentCenter)
                                   }];
            }
//            std::size_t idx = 0;
//            std::for_each(anchors().begin(), anchors().end(), [&](auto& i) {
//                Float x = r.left() + r.width() * idx / (anchors().count() - 1);
//                CGContextMoveToPoint(ctx, x, r.bottom());
//                CGContextAddLineToPoint(ctx, x, r.bottom() + 3);
//                CGContextStrokePath(ctx);
//
//                NSString *text = nullptr;
//                if (anchors().formatter()) {
//                    const char *str = anchors().formatter()(i).c_str();
//                    if (str) {
//                        text = [NSString stringWithCString:str encoding:NSUTF8StringEncoding];
//                    }
//                    else {
//                        text = @"";
//                    }
//                }
//                else {
//                    text = [NSString stringWithFormat:@"%d", (int)i];
//                }
//                [text drawAtPoint:CGPointMake(x - 10, r.bottom() + 5)
//                   withAttributes:@{ NSForegroundColorAttributeName: UIColorFrom(textColor()) }];
//                ++idx;
//            });
        }
        
        // stroke triangle
        CGContextMoveToPoint(ctx, r.right() + triangleHeight(), r.bottom());
        CGContextAddLineToPoint(ctx, r.right() + triangleHeight(), r.bottom() - 3);
        CGContextAddLineToPoint(ctx, r.right() + triangleHeight() + 10, r.bottom());
        CGContextAddLineToPoint(ctx, r.right() + triangleHeight(), r.bottom() + 3);
        CGContextClosePath(ctx);
        
        CGContextSetFillColor(ctx, color());
        CGContextFillPath(ctx);
        
        // stroke name
        CGContextSetStrokeColor(ctx, textColor());
        NSString *text = [NSString stringWithCString:name().c_str() encoding:NSUTF8StringEncoding];
        [text drawAtPoint:CGPointMake(r.right() + triangleHeight() - 5, r.bottom() + 8)
           withAttributes:@{ NSForegroundColorAttributeName: UIColorFrom(textColor()) }];
        
        CGContextRestoreGState(ctx);
        
        
        super::Draw();
    }
    
    void YAxisLayer::Draw() {
        auto ctx = canvas()->context();
        auto r = absoluteFrame();
        
        CGContextSaveGState(ctx);
        
        // stroke line
        CGContextMoveToPoint(ctx, r.left(), r.bottom());
        CGContextAddLineToPoint(ctx, r.left(), r.top() - triangleHeight());
        
        CGContextSetStrokeColor(ctx, color());
        CGContextStrokePath(ctx);
        
        // stroke anchor
        if (anchors() && anchors()->count()) {
            // stroke anchor
            for (int i = 0; i < anchors()->count(); ++i) {
                Float y = r.bottom() - r.height() * anchors()->positionAt(i);
                
                CGContextMoveToPoint(ctx, r.left(), y);
                CGContextAddLineToPoint(ctx, r.left() - 3, y);
                CGContextStrokePath(ctx);
                
                NSString *text = nullptr;
                std::string str = anchors()->nameAt(i);
                if (str.size()) {
                    text = [NSString stringWithCString:str.c_str() encoding:NSUTF8StringEncoding];
                }
                else {
                    text = @"";
                }
                
                [text drawInRect:CGRectMake(0, y - 8, r.left(), 14)
                  withAttributes:@{
                                   NSForegroundColorAttributeName: UIColorFrom(textColor()),
                                   NSFontAttributeName: [UIFont systemFontOfSize:12],
//                                   NSTextAlignment: @(NSTextAlignmentCenter)
                                   }];
            }
        }
        /*
        std::size_t idx = 0;
        std::for_each(anchors().begin(), anchors().end(), [&](auto& i) {
            Float y = r.bottom() - r.height() * idx / (anchors().count() - 1);
            CGContextMoveToPoint(ctx, r.left(), y);
            CGContextAddLineToPoint(ctx, r.left() - 3, y);
            CGContextStrokePath(ctx);
            
            NSString *text = nil;
            if (anchors().formatter()) {
                const char *str = anchors().formatter()(i).c_str();
                if (str) {
                    text = [NSString stringWithCString:str encoding:NSUTF8StringEncoding];
                }
                else {
                    text = @"";
                }
            }
            else {
                text = [NSString stringWithFormat:@"%d", (int)i];
            }
            [text drawAtPoint:CGPointMake(r.left() - 20, y - 8)
               withAttributes:@{ NSForegroundColorAttributeName: UIColorFrom(textColor()) }];
            ++idx;
        });*/
        
        // stroke triangle
        CGContextMoveToPoint(ctx, r.left(), r.top() - triangleHeight());
        CGContextAddLineToPoint(ctx, r.left() - 3, r.top() - triangleHeight());
        CGContextAddLineToPoint(ctx, r.left(), r.top() - triangleHeight() - 10);
        CGContextAddLineToPoint(ctx, r.left() + 3, r.top() - triangleHeight());
        CGContextClosePath(ctx);
        
        CGContextSetFillColor(ctx, color());
        CGContextFillPath(ctx);
        
        // stroke name
        CGContextSetStrokeColor(ctx, textColor());
        NSString *text = [NSString stringWithCString:name().c_str() encoding:NSUTF8StringEncoding];
        [text drawAtPoint:CGPointMake(r.left() + 8, r.top() - triangleHeight() + 5)
           withAttributes:@{ NSForegroundColorAttributeName: UIColorFrom(textColor()) }];
        
        CGContextRestoreGState(ctx);
        
        super::Draw();
    }
    
}
