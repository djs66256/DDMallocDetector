//
//  MDDrawableView.m
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/29.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDDrawableView.h"

@interface MDDrawableView() {
    std::shared_ptr<MD::CanvasLayer> _canvas;
}

@end

@implementation MDDrawableView

- (const std::shared_ptr<MD::CanvasLayer>&)canvas {
    if (!_canvas) {
        _canvas = std::make_shared<MD::CanvasLayer>();
        MD::Color color = { 1, 1, 1, 1 };
        _canvas->setBackgroundColor(color);
    }
    return _canvas;
}

- (void)drawRect:(CGRect)rect {
    if (_canvas) {
        _canvas->setFrame(self.bounds);
        _canvas->Draw();
    }
}


@end
