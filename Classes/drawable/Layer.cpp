//
//  Layer.cpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/29.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include <stdio.h>
#include "Layer.hpp"
#include "CanvasLayer.h"

namespace MD {
    
    void Layer::AddLayer(std::shared_ptr<Layer> layer) noexcept {
        layer->super_layer_ = this;
        sub_layers_.emplace_back(layer);
    }
    
    void Layer::RemoveLayer(Layer* layer) noexcept {
        auto idx = std::find_if(sub_layers_.begin(), sub_layers_.end(), [=](auto& l) {
            return l.get() == layer;
        });
        if (idx != sub_layers_.end()) {
            layer->super_layer_ = nullptr;
            sub_layers_.erase(idx);
        }
    }
    
    void Layer::RemoveLayer(std::shared_ptr<Layer> &layer) noexcept {
        RemoveLayer(layer.get());
    }
    
    void Layer::RemoveLayers() noexcept {
        std::for_each(sub_layers_.begin(), sub_layers_.end(), [](auto& layer) {
            layer->super_layer_ = nullptr;
        });
        sub_layers_.clear();
    }
    
    void Layer::Draw() {
        std::for_each(sub_layers_.begin(), sub_layers_.end(), [](auto& layer) {
            layer->Draw();
        });
    }
    
    CanvasLayer* Layer::canvas() const {
        if (this->isCanvas()) {
            return static_cast<CanvasLayer*>(const_cast<Layer*>(this));
        }
        if (super_layer_ == nullptr) {
            return nullptr;
        }
        return super_layer_->canvas();
    }
    
    Rect Layer::absoluteFrame() const {
        CanvasLayer* cvs = canvas();
        if (cvs == nullptr) {
            return Rect();
        }
        if (this == cvs) {
            return cvs->frame();
        }
        
        auto layer = superLayer();
        auto e = edges_;
        while (layer != cvs) {
            e += layer->edges();
        }
        return cvs->frame().inset(e);
    }
}
