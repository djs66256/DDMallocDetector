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
#include "Layer.hpp"

namespace MD {
    
    class AxisLayer : public Layer {
    public:
        AxisLayer() = default;
        AxisLayer(std::string&& name) : name_(name) {}
        
        class Anchors {
        public:
            class Iterator {
            public:
                Iterator(Float delta, int count)
                : delta_(delta), count_(count) {}
                
                bool operator== (const Iterator& i) { return count_ == i.count_; }
                bool operator!= (const Iterator& i) { return !(*this == i); }
                Float& operator* () { return current_; }
                Iterator& operator++ () {
                    --count_;
                    current_ += delta_;
                    return *this;
                }
            private:
                Float delta_ = 0;
                Float current_ = 0;
                int count_ = 0;
            };
            
            void Prepare() {
                if (max_ > min_ && max_count_ > 0) {
                    Float delta = delta_;
                    count_ = fabs(floor((max_ - min_) / delta_)) + 1;
                    while (count_ > max_count_) {
                        delta *= 2;
                        count_ = fabs(ceil((max_ - min_) / delta_));
                    }
                    real_delta_ = delta;
                    // 1 point is just zero.
                    if (count_ == 1) {
                        real_delta_ = 0;
                        count_ = 0;
                    }
                }
                else {
                    real_delta_ = 0;
                    count_ = 0;
                }
            }
            
            Float min() const { return min_; }
            void setMin(Float m) { min_ = m; }
            
            Float max() const { return max_; }
            void setMax(Float m) { max_ = m; }
            
            Float delta() const { return delta_; }
            void setDelta(Float d) { delta_ = d; }
            
            int maxCount() const { return max_count_; }
            void setMaxCount(int c) { max_count_ = c; }
            
            int count() const { return count_; }
            
            Iterator begin() const {
                return Iterator(delta_, count_);
            }
            Iterator end() const {
                return Iterator(0, 0);
            }
            
            bool hasValue() const {
                return count_ > 0;
            }
            
            typedef std::function<std::string&& (Float)> formatter_type;
            void setFormatter(formatter_type f) { formatter_ = f; }
            const formatter_type& formatter() const { return formatter_; }
            
            friend class Iterator;
        private:
            Float delta_ = 1;
            Float min_ = 0;
            Float max_ = 0;
            int max_count_ = 5;
            int count_ = 0;
            Float real_delta_ = 0;
            formatter_type formatter_;
        };
        
        void setRange(Float min, Float max) { anchors_.setMin(min); anchors_.setMax(max); }
        Float min() { return anchors_.min(); }
        Float max() { return anchors_.max(); }
        const Anchors& anchors() const { return anchors_; }
        Anchors* getAnchors() { return &anchors_; }
        
        void setName(std::string&& name) { name_ = name; }
        const std::string& name() const { return name_; }
        
        Float triangleHeight() const { return triangle_height_; }
        void setTriangleHeight(Float h) { triangle_height_ = h; }
        
        Color& color() { return color_; }
        void setColor(Color& clr) { color_ = clr; }
        
        Color& textColor() { return text_color_; }
        void setTextColor(Color& clr) { text_color_ = clr; }
        
    private:
        Float triangle_height_ = 20;
        std::string name_;
        Color text_color_;
        Color color_;
        Anchors anchors_;
    };
    
    class XAxisLayer : public AxisLayer {
    public:
        typedef AxisLayer super;
        
        XAxisLayer() : super("X") {}
        XAxisLayer(std::string&& name) : super(std::forward<std::string>(name)) {}
        
        void Draw() override;
    };
    
    class YAxisLayer : public AxisLayer {
    public:
        typedef AxisLayer super;
        
        YAxisLayer() : super("Y") {}
        YAxisLayer(std::string&& name) : super(std::forward<std::string>(name)) {}
        
        void Draw() override;
    };
}

#endif /* AxisLayer_hpp */
