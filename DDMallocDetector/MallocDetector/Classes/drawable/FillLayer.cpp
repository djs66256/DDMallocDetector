//
//  FillLayer.cpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/30.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include "FillLayer.hpp"
#include "CanvasLayer.h"

namespace MD {
    void FillLayer::Draw() {
        auto ctx = canvas()->context();
        CGContextSaveGState(ctx);
        Rect r = absoluteFrame();
        CGContextSetFillColor(ctx, backgroundColor());
        CGContextFillRect(ctx, r);
        CGContextRestoreGState(ctx);
        super::Draw();
    }
}
