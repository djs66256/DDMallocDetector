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
#include "AxisAnchors.hpp"

namespace MD {
    
    
    class AxisLayer : public Layer {
    public:
        AxisLayer() = default;
        AxisLayer(std::string&& name) : name_(name) {}
        
        std::shared_ptr<Anchors> anchors() { return anchors_; }
        void setAnchors(std::shared_ptr<Anchors> anchors) { anchors_ = anchors; }
        // Anchors* getAnchors() { return &anchors_; }
        
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
        std::shared_ptr<Anchors> anchors_;
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
