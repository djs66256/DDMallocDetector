//
//  MDDrawableView.h
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/29.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "CanvasLayer.h"
#include "StrokeLayer.hpp"
#include "AxisLayer.hpp"

@interface MDDrawableView : UIView {
@protected
    std::shared_ptr<MD::AxisLayer> _xAxis;
    std::shared_ptr<MD::AxisLayer> _yAxis;
    std::shared_ptr<MD::FillLayer> _contentLayer;
}


- (const std::shared_ptr<MD::CanvasLayer>&)canvas;
- (void)setNeedsRebuildCanvas;
- (void)rebuildCanvasIfNeeded;
- (void)rebuildCanvas NS_REQUIRES_SUPER;

- (std::shared_ptr<MD::AxisLayer>)makeXAxis;
- (std::shared_ptr<MD::AxisLayer>)makeYAxis;

@end
