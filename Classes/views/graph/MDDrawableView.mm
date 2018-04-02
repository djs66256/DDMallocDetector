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
    BOOL _rebuildCanvas;
}

@end

@implementation MDDrawableView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _xAxis = std::make_shared<MD::XAxisLayer>();
        _xAxis->setTriangleHeight(10);
        _xAxis->setTextColor(0, 0, 0);
        _yAxis = std::make_shared<MD::YAxisLayer>();
        _contentLayer = std::make_shared<MD::FillLayer>();
        
        _canvas = std::make_shared<MD::CanvasLayer>();
        _canvas->setBackgroundColor({ 1, 1, 1, 1 });
        
        _contentLayer->setEdges(MD::Edges(20, 100, 20, 100));
        _contentLayer->setBackgroundColor({0.9, 0.9, 0.9});
        
        
        _xAxis->setName("X");
        _xAxis->setEdges(MD::Edges(20, 100, 20, 100));
        
        
        _yAxis->setName("Y");
        _yAxis->setEdges(MD::Edges(20, 100, 20, 100));
    }
    return self;
}

- (const std::shared_ptr<MD::CanvasLayer>&)canvas {
    return _canvas;
}

- (void)setNeedsRebuildCanvas {
    _rebuildCanvas = YES;
}

- (void)rebuildCanvasIfNeeded {
    if (_rebuildCanvas) {
        _rebuildCanvas = NO;
        [self rebuildCanvas];
        [self setNeedsDisplay];
    }
}

- (void)rebuildCanvas {
    auto& canvas = [self canvas];
    canvas->RemoveLayers();
    canvas->AddLayer(_contentLayer);
    canvas->AddLayer(_xAxis);
    canvas->AddLayer(_yAxis);
}

- (void)drawRect:(CGRect)rect {
    if (_canvas) {
        _canvas->setFrame(self.bounds);
        _canvas->Draw();
    }
}


@end
