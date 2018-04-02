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
#include <initializer_list>
#include "Layer.hpp"
#include "CanvasLayer.h"
#include "StrokeLayerHelper.hpp"

namespace MD {
    template<class _V, class _Loc = AvarageLocation<_V>>
    class StrokeLayer : public Layer {
    public:
        typedef _V value_type;
        typedef typename std::shared_ptr<std::vector<value_type>> line_type;
        typedef _Loc location_type;
        
        void setColor(CGFloat r, CGFloat g, CGFloat b, CGFloat a = 1) {
            color_.setComponents(r, g, b, a);
        }
        void setColor(Color& c) { color_ = c; }
        Color& color() { return color_; }
        
        void setLineWidth(CGFloat width) { line_width_ = width; }
        CGFloat lineWidth() const { return line_width_; }
        
        const FloatRange& xRange() const { return xRange_; }
        void setXRange(FloatRange r) { xRange_ = r; }
        void setXRange(Float min, Float max) { xRange_.min = min; xRange_.max = max; }
        const FloatRange& yRange() const { return yRange_; }
        void setYRange(FloatRange r) { yRange_ = r; }
        void setYRange(Float min, Float max) { yRange_.min = min; yRange_.max = max; }
        
        void setLine(line_type line) { line_ = line; }
        void setLine(line_type&& line) { line_ = line; }
        
        void Draw() override;
        
    protected:
        
        
    private:
        FloatRange xRange_ = {0, 0};
        FloatRange yRange_ = {0, 0};
        line_type line_;
        Color color_;
        CGFloat line_width_ = 1;
    };
    
    typedef StrokeLayer<int64_t> IntStrokeLayer;
    template<class _T1, class _T2>
    class PairStrokeLayer : public StrokeLayer<std::pair<_T1, _T2>, PairLocation<std::pair<_T1, _T2>>> {
        
    };
    template<class _T1, class _T2>
    class PairLinearStrokeLayer : public StrokeLayer<std::pair<_T1, _T2>, PairLinearLocation<std::pair<_T1, _T2>>> {
        
    };
    
#if 0
#define LOG(x, y) printf("(%f, %f)\n", x, y)
#else
#define LOG(x, y)
#endif
    
    static inline void MoveTo(CGContextRef ctx, Float x, Float y) {
        LOG(x, y);
        CGContextMoveToPoint(ctx, x, y);
    }
    static inline void AddLineTo(CGContextRef ctx, Float x, Float y) {
        LOG(x, y);
        CGContextAddLineToPoint(ctx, x, y);
    }
    
#undef LOG
    
    template<class _V, class _Loc>
    void StrokeLayer<_V, _Loc>::Draw() {
        if (!line_ || line_->size() <= 1 
          || xRange_.min >= xRange_.max
          || yRange_.min >= yRange_.max) {
            return;
        }
        Rect r = absoluteFrame();
        CGContextRef ctx = canvas()->context();
        CGContextSaveGState(ctx);
        
        _Loc loc(r, xRange_, yRange_, line_->size());
        auto i = line_->begin();
        MoveTo(ctx, loc.x(*i), loc.y(*i));
        ++i;
        for (; i != line_->end(); ++i) {
            AddLineTo(ctx, loc.x(*i), loc.y(*i));
        }

        CGContextSetStrokeColor(ctx, color_);
        CGContextSetLineWidth(ctx, line_width_);
        CGContextStrokePath(ctx);
        
        CGContextRestoreGState(ctx);
    }
}

#endif /* StrokeLayer_hpp */
