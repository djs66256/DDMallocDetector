//
//  MDStatisticsView.m
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/29.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDStatisticsView.h"
#include "StrokeLayer.hpp"
#include "AxisLayer.hpp"

@interface MDStatisticsView () {
    std::shared_ptr<MD::View::Lines> _lines;
    BOOL _rebuildCanvas;
    
    std::shared_ptr<MD::XAxisLayer> _xAxis;
    std::shared_ptr<MD::YAxisLayer> _yAxis;
}

@end

@implementation MDStatisticsView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _xAxis = std::make_shared<MD::XAxisLayer>();
        _xAxis->setEdges(MD::Edges(20, 100, 20, 100));
        _xAxis->setRange(0, 8);
        _xAxis->getAnchors()->setMaxCount(10);
        _xAxis->getAnchors()->setDelta(1);
        _xAxis->setTriangleHeight(10);
        
        _yAxis = std::make_shared<MD::YAxisLayer>();
        _yAxis->setEdges(MD::Edges(20, 100, 20, 100));
        _yAxis->setRange(0, 10);
        _yAxis->getAnchors()->setMaxCount(20);
        _yAxis->getAnchors()->setDelta(1);
    }
    return self;
}

- (void)setNeedsRebuildCanvas {
    _rebuildCanvas = YES;
}

- (void)rebuildCanvasIfNeeded {
    if (_rebuildCanvas) {
        auto& canvas = self.canvas;
        canvas->RemoveLayers();
        auto contentLayer = std::make_shared<MD::FillLayer>();
        contentLayer->setEdges(MD::Edges(20, 100, 20, 100));
        contentLayer->setBackgroundColor({0.2, 0.2, 0.2});
        canvas->AddLayer(contentLayer);
        canvas->AddLayer(_xAxis);
        canvas->AddLayer(_yAxis);
        if (_lines) {
            std::for_each(_lines->begin(), _lines->end(), [&](auto& line) {
                auto layer = std::make_shared<MD::IntStrokeLayer>();
                layer->setEdges(MD::Edges(20, 100, 20, 100));
                layer->setColor(1, 0, 0);
                layer->setLine(line, 0, 10);
                canvas->AddLayer(layer);
            });
        }
    }
}

- (void)setLines:(std::shared_ptr<MD::View::Lines>)lines {
    _lines = lines;
    
    [self setNeedsRebuildCanvas];
}

@end
