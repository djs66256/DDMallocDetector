//
//  StrokeLayer.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/29.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef StrokeLayer_hpp
#define StrokeLayer_hpp

#include <stdio.h>
#include <CoreGraphics/CoreGraphics.h>
#include <vector>
#include "Layer.hpp"
#include "CanvasLayer.h"

namespace MD {
    template<class _V>
    class StrokeLayer : public Layer {
    public:
        typedef _V value_type;
        typedef typename std::shared_ptr<std::vector<value_type>> line_type;
        
        void setColor(CGFloat r, CGFloat g, CGFloat b, CGFloat a = 1) {
            color_.setComponents(r, g, b, a);
        }
        void setColor(Color& c) { color_ = c; }
        Color& color() { return color_; }
        
        void setLineWidth(CGFloat width) { line_width_ = width; }
        CGFloat lineWidth() const { return line_width_; }
        
        void setLine(line_type line, value_type min, value_type max) {
            max_ = max;
            min_ = min;
            line_ = line;
        }
        
        void setLine(line_type line) {
            auto first = line->begin();
            value_type max = *first;
            value_type min = *first;
            std::for_each(++first, line->end(), [&](value_type& i) {
                if (max < i) {
                    max = i;
                }
                if (min > i) {
                    min = i;
                }
            });
            setLine(line, max, min);
        }
        
        void Draw() override {
            if (!line_ || line_->size() <= 1 || max_ < min_) {
                return;
            }
            Rect r = absoluteFrame();
            CGContextRef ctx = canvas()->context();
            CGContextSaveGState(ctx);
            
            CGFloat height = max_ == min_ ? 100 : static_cast<CGFloat>(max_ - min_);
            CGFloat deltaY = r.size.height / height;
            CGFloat deltaX = r.size.width / (line_->size() - 1);
            auto i = line_->begin();
            CGFloat x = r.origin.x;
//            CGFloat minY = r.origin.y;
            CGFloat maxY = r.size.height + r.origin.y;
            CGContextMoveToPoint(ctx, x, maxY - (static_cast<CGFloat>(*i) - min_) * deltaY);
            x += deltaX;
            ++i;
            for (; i != line_->end(); ++i, x += deltaX) {
                CGContextAddLineToPoint(ctx, x, maxY - (static_cast<CGFloat>(*i) - min_) * deltaY);
            }
            
            CGContextSetStrokeColor(ctx, color_);
            CGContextSetLineWidth(ctx, line_width_);
            CGContextStrokePath(ctx);
            
            CGContextRestoreGState(ctx);
        }
        
    protected:
        
        
    private:
        value_type max_;
        value_type min_;
        line_type line_;
        Color color_;
        CGFloat line_width_ = 1;
    };
    
    typedef StrokeLayer<int64_t> IntStrokeLayer;
}

#endif /* StrokeLayer_hpp */
