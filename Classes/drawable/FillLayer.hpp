//
//  FillLayer.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/30.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef FillLayer_hpp
#define FillLayer_hpp

#include <stdio.h>
#include "Layer.hpp"

namespace MD {
    class FillLayer : public Layer {
    public:
        typedef Layer super;
        
        void setBackgroundColor(Color color) {
            background_color_ = color;
        }
        Color& backgroundColor() { return background_color_; }
        
        void Draw() override;
        
    private:
        Color background_color_;
    };
}

#endif /* FillLayer_hpp */
