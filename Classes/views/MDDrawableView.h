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

@interface MDDrawableView : UIView


- (const std::shared_ptr<MD::CanvasLayer>&)canvas;

@end
