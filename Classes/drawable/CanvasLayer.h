//
//  CanvasLayer.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/29.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef CanvasLayer_hpp
#define CanvasLayer_hpp

#include <stdio.h>
#include <CoreGraphics/CoreGraphics.h>
#include "FillLayer.hpp"

namespace MD {
    class CanvasLayer : public FillLayer {
    public:
        typedef FillLayer super;
        
        void Draw() override;
        
        void Draw(CGContextRef ctx);
        
        
        Rect frame() const {
            return rect_;
        }
        
        void setFrame(Rect rect) {
            rect_ = rect;
        }
        
        Size size() const {
            return rect_.size;
        }
        
        void setSize(Size size) {
            rect_.size = size;
        }
        
        Float width() const {
            return rect_.size.width;
        }
        
        Float height() const {
            return rect_.size.height;
        }
        
        Point origin() const {
            return rect_.origin;
        }
        
        void setOrigin(Point point) {
            rect_.origin = point;
        }
        
        CGContextRef context() {
            return ctx_;
        }
    protected:
        bool isCanvas() const override {
            return true;
        }
        
    private:
        Rect rect_;
        CGContextRef ctx_;
    };
}

#endif /* CanvasLayer_hpp */
