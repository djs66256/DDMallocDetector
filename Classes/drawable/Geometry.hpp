//
//  Geometry.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/29.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include <stdio.h>
#include <CoreGraphics/CGGeometry.h>

namespace MD {
    
    typedef CGFloat Float;
    struct Point {
        Float x = 0;
        Float y = 0;
        
        Point() {}
        Point(Float x, Float y) : x(x), y(y) {}
        Point(CGPoint p): x(p.x), y(p.y) {}
        
        Point& operator= (const Point& p) noexcept {
            x = p.x; y = p.x;
            return *this;
        }
    };
    inline Point operator + (const Point l, const Point r) noexcept {
        Point p(l.x + r.x, l.y + r.y);
        return p;
    }
    
    struct Size {
        Float width = 0;
        Float height = 0;
        
        Size() {}
        Size(Float w, Float h) : width(w), height(h) {}
        Size(CGSize s) : width(s.width), height(s.height) {}
        
        Size& operator= (const Size& s) noexcept {
            width = s.width; height = s.height;
            return *this;
        }
        friend Size operator + (const Size l, const Size r) noexcept {
            Size s(l.width + r.width, l.height + r.height);
            return s;
        }
    };
    
    struct Edges {
        Float left = 0, top = 0, right = 0, bottom = 0;
        
        Edges() {}
        Edges(Float l, Float t, Float r, Float b) : left(l), top(t), right(r), bottom(b) {}
//        Edges(UIEdgeInsets e) : left(e.left), top(e.top), right(e.right), bottom(e.bottom) {}
        
        inline Edges& operator+= (const Edges& r) noexcept {
            left += r.left;
            top += r.top;
            right += r.right;
            bottom += r.bottom;
            return *this;
        }
        friend Edges operator+ (const Edges& l, const Edges& r) noexcept {
            return Edges(l.left + r.left, l.top + r.top, l.right + r.right, l.bottom + r.bottom);
        }
    };
    
    struct Rect {
        Point origin;
        Size size;
        
        Rect() {}
        Rect(CGRect r) : origin(r.origin), size(r.size) { }
        
        Float top() { return origin.y; }
        Float left() { return origin.x; }
        Float right() { return origin.x + size.width; }
        Float bottom() { return origin.y + size.height; }
        Float width() { return size.width; }
        Float height() { return size.height; }
        
        Rect& operator= (const Rect& r) noexcept {
            origin = r.origin; size = r.size;
            return *this;
        }
        
        Rect inset(const Edges& edge) noexcept {
            Rect r;
            r.origin.x = origin.x + edge.left;
            r.origin.y = origin.y + edge.top;
            r.size.height = size.height - (edge.top + edge.bottom);
            r.size.width = size.width - (edge.right + edge.left);
            return r;
        }
        
        operator CGRect() const noexcept {
            return CGRectMake(origin.x, origin.y, size.width, size.height);
        }
    };
}

#endif /* Geometry_hpp */
