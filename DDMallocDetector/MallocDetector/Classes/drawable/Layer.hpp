//
//  Layer.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/28.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef Layer_hpp
#define Layer_hpp

#include <stdio.h>
#include <memory>
#include <vector>
#include "Geometry.hpp"
#include "Drawable.hpp"
#include "Color.h"
#include "../base/Macros.h"

namespace MD {
    class CanvasLayer;
    
    class Layer : public Drawable {
    public:
        Layer() {}
        
        Edges edges() const { return edges_; }
        void setEdges(const Edges& e) {
            edges_ = e;
        }
        void setEdges(const Edges&& e) {
            edges_ = e;
        }
        
        Layer* superLayer() const {
            return super_layer_;
        }
        
        void AddLayer(std::shared_ptr<Layer> layer) noexcept;
        void RemoveLayer(Layer* layer) noexcept;
        void RemoveLayer(std::shared_ptr<Layer>& layer) noexcept;
        void RemoveLayers() noexcept;
        
        void Draw() override;
        
        virtual ~Layer() {
            RemoveLayers();
        }
        
    protected:
        virtual bool isCanvas() const {
            return false;
        }
        
        CanvasLayer* canvas() const;
        Rect absoluteFrame() const;
        
    private:
        MD_NO_COPY(Layer);
        
        Edges edges_;
        Layer *super_layer_ = nullptr;
        std::vector<std::shared_ptr<Layer> > sub_layers_;
    };
}

#endif /* Layer_hpp */
