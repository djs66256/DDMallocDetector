//
//  AxisLayer.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/30.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef AxisLayer_hpp
#define AxisLayer_hpp

#include <stdio.h>
#include <string>
#include <cmath>
#include <functional>
#include <UIKit/UIKit.h>
#include "Layer.hpp"
#include "AxisAnchors.hpp"

namespace MD {
    
    class AxisLayer : public Layer {
    public:
        AxisLayer() = default;
        AxisLayer(std::string&& name) : name_(std::move(name)) {}
        
        void setName(std::string&& name) { name_ = name; }
        const std::string& name() const { return name_; }
        
        Float triangleHeight() const { return triangle_height_; }
        void setTriangleHeight(Float h) { triangle_height_ = h; }
        
        Color& color() { return color_; }
        void setColor(Color& clr) { color_ = clr; }
        
        Color& textColor() { return text_color_; }
        void setTextColor(Color& clr) { text_color_ = clr; }
        void setTextColor(float r, float g, float b, float a = 1) {
            text_color_.setComponents(r, g, b, a);
        }
        
    private:
        Float triangle_height_ = 20;
        std::string name_;
        Color text_color_;
        Color color_;
    };
    
    
    template<class _A = LinearAnchors<double>>
    class AnchorsAxisLayer : public AxisLayer {
    public:
        typedef _A anchors_type;
        
        anchors_type& anchors() { return anchors_; }
        
    private:
        anchors_type anchors_;
    };
    
    template<class _A = LinearAnchors<double>>
    class XAxisLayer : public AnchorsAxisLayer<_A> {
    public:
        typedef AnchorsAxisLayer<_A> super;
        
        XAxisLayer() : XAxisLayer("X") {}
        XAxisLayer(std::string&& name) {
            AxisLayer::setName(std::move(name));
        }
        
        void Draw() override;
    };
    
    template<class _A = LinearAnchors<double>>
    class YAxisLayer : public AnchorsAxisLayer<_A> {
    public:
        typedef AnchorsAxisLayer<_A> super;
        
        YAxisLayer() : YAxisLayer("Y") {}
        YAxisLayer(std::string&& name) {
            AxisLayer::setName(std::move(name));
        }
        
        void Draw() override;
    };
    
    inline UIColor* UIColorFrom(Color& c) {
        return [UIColor colorWithRed:c.red() green:c.green() blue:c.blue() alpha:c.alpha()];
    }
    
    template<class _T>
    void XAxisLayer<_T>::Draw() {
        auto ctx = AxisLayer::canvas()->context();
        auto r = AxisLayer::absoluteFrame();
        
        CGContextSaveGState(ctx);
        
        // stroke line
        CGContextMoveToPoint(ctx, r.left(), r.bottom());
        CGContextAddLineToPoint(ctx, r.right() + AxisLayer::triangleHeight(), r.bottom());
        
        CGContextSetStrokeColor(ctx, AxisLayer::color());
        CGContextStrokePath(ctx);
        
        auto& anchors = super::anchors();
        if (anchors.count()) {
            // stroke anchor
            for (int i = 0; i < anchors.count(); ++i) {
                Float x = r.left() + r.width() * anchors.positionAt(i);
                
                CGContextMoveToPoint(ctx, x, r.bottom());
                CGContextAddLineToPoint(ctx, x, r.bottom() + 3);
                CGContextStrokePath(ctx);
                
                NSString *text = nullptr;
                std::string str = anchors.nameAt(i);
                if (str.size()) {
                    text = [NSString stringWithCString:str.c_str() encoding:NSUTF8StringEncoding];
                }
                else {
                    text = @"";
                }
                
                [text drawInRect:CGRectMake(x - 8, r.bottom() + 8, 20*2, 14)
                  withAttributes:@{
  NSForegroundColorAttributeName: UIColorFrom(AxisLayer::textColor()),
             NSFontAttributeName: [UIFont systemFontOfSize:12],
                 //                                   NSattname: @(NSTextAlignmentCenter)
                 }];
            }
        }
        
        // stroke triangle
        CGContextMoveToPoint(ctx, r.right() + AxisLayer::triangleHeight(), r.bottom());
        CGContextAddLineToPoint(ctx, r.right() + AxisLayer::triangleHeight(), r.bottom() - 3);
        CGContextAddLineToPoint(ctx, r.right() + AxisLayer::triangleHeight() + 10, r.bottom());
        CGContextAddLineToPoint(ctx, r.right() + AxisLayer::triangleHeight(), r.bottom() + 3);
        CGContextClosePath(ctx);
        
        CGContextSetFillColor(ctx, AxisLayer::color());
        CGContextFillPath(ctx);
        
        // stroke name
        CGContextSetStrokeColor(ctx, AxisLayer::textColor());
        NSString *text = [NSString stringWithCString:AxisLayer::name().c_str() encoding:NSUTF8StringEncoding];
        [text drawAtPoint:CGPointMake(r.right() + AxisLayer::triangleHeight() - 5, r.bottom() + 8)
           withAttributes:@{ NSForegroundColorAttributeName: UIColorFrom(AxisLayer::textColor()) }];
        
        CGContextRestoreGState(ctx);
        
        
        super::Draw();
    }
    
    template<class _T>
    void YAxisLayer<_T>::Draw() {
        auto ctx = AxisLayer::canvas()->context();
        auto r = AxisLayer::absoluteFrame();
        
        CGContextSaveGState(ctx);
        
        // stroke line
        CGContextMoveToPoint(ctx, r.left(), r.bottom());
        CGContextAddLineToPoint(ctx, r.left(), r.top() - AxisLayer::triangleHeight());
        
        CGContextSetStrokeColor(ctx, AxisLayer::color());
        CGContextStrokePath(ctx);
        
        auto& anchors = super::anchors();
        
        // stroke anchor
        if (anchors.count()) {
            // stroke anchor
            for (int i = 0; i < anchors.count(); ++i) {
                Float y = r.bottom() - r.height() * anchors.positionAt(i);
                
                CGContextMoveToPoint(ctx, r.left(), y);
                CGContextAddLineToPoint(ctx, r.left() - 3, y);
                CGContextStrokePath(ctx);
                
                NSString *text = nullptr;
                std::string str = anchors.nameAt(i);
                if (str.size()) {
                    text = [NSString stringWithCString:str.c_str() encoding:NSUTF8StringEncoding];
                }
                else {
                    text = @"";
                }
                
                [text drawInRect:CGRectMake(0, y - 8, r.left(), 14)
                  withAttributes:@{
  NSForegroundColorAttributeName: UIColorFrom(AxisLayer::textColor()),
             NSFontAttributeName: [UIFont systemFontOfSize:12],
                 //                                   NSTextAlignment: @(NSTextAlignmentCenter)
                 }];
            }
        }
        
        // stroke triangle
        CGContextMoveToPoint(ctx, r.left(), r.top() - AxisLayer::triangleHeight());
        CGContextAddLineToPoint(ctx, r.left() - 3, r.top() - AxisLayer::triangleHeight());
        CGContextAddLineToPoint(ctx, r.left(), r.top() - AxisLayer::triangleHeight() - 10);
        CGContextAddLineToPoint(ctx, r.left() + 3, r.top() - AxisLayer::triangleHeight());
        CGContextClosePath(ctx);
        
        CGContextSetFillColor(ctx, AxisLayer::color());
        CGContextFillPath(ctx);
        
        // stroke name
        CGContextSetStrokeColor(ctx, AxisLayer::textColor());
        NSString *text = [NSString stringWithCString:AxisLayer::name().c_str() encoding:NSUTF8StringEncoding];
        [text drawAtPoint:CGPointMake(r.left() + 8, r.top() - AxisLayer::triangleHeight() + 5)
           withAttributes:@{ NSForegroundColorAttributeName: UIColorFrom(AxisLayer::textColor()) }];
        
        CGContextRestoreGState(ctx);
        
        super::Draw();
    }
}

#endif /* AxisLayer_hpp */
