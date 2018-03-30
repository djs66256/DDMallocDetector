//
//  CanvasLayer.cpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/29.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include <UIKit/UIKit.h>
#include "CanvasLayer.h"

namespace MD {
    void CanvasLayer::Draw() {
        ctx_ = UIGraphicsGetCurrentContext();
        super::Draw();
    }
    
    void CanvasLayer::Draw(CGContextRef ctx)  {
        ctx_ = ctx;
        super::Draw();
    }
}
