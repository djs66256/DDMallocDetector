//
//  Color.h
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/30.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef Color_h
#define Color_h

#include <stdio.h>
#include <CoreGraphics/CGGeometry.h>

namespace MD {
    class Color {
    public:
        typedef CGFloat color_type[4];
        
        Color() : color_{0, 0, 0, 1} { };
        Color(Float r, Float g, Float b, Float a = 1) : color_{r, g, b, a} { }
        Color(const Color& c) { *this = c; }
        Color(const Color&& c) { *this = c; }
        
        Float red() const { return color_[0]; }
        Float green() const { return color_[1]; }
        Float blue() const { return color_[2]; }
        Float alpha() const { return color_[3]; }
        void setComponents(Float r, Float g, Float b, Float a = 1) {
            color_[0] = r;
            color_[1] = g;
            color_[2] = b;
            color_[3] = a;
        }
        
        Color& operator= (const Color& c) {
            color_[0] = c.color_[0]; color_[1] = c.color_[1]; color_[2] = c.color_[2]; color_[3] = c.color_[3];
            return *this;
        }
        
        operator const CGFloat* () {
            return color_;
        }
        
    private:
        color_type color_;
    };
}


#endif /* Color_h */
