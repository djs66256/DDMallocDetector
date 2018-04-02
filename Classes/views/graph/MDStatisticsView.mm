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
    
}

@end

@implementation MDStatisticsView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _xAxis->setEdges(MD::Edges(20, 100, 20, 100));
        _xAxis->setTriangleHeight(10);
        
        _yAxis->setEdges(MD::Edges(20, 100, 20, 100));
    }
    return self;
}

- (void)rebuildCanvas {
    [super rebuildCanvas];
    auto& canvas = self.canvas;
    _contentLayer->setEdges(MD::Edges(20, 100, 20, 100));
    _contentLayer->setBackgroundColor({0.2, 0.2, 0.2});
    if (_lines) {
        std::for_each(_lines->begin(), _lines->end(), [&](std::shared_ptr<MD::View::Line>& line) {
            auto layer = std::make_shared<MD::IntStrokeLayer>();
            layer->setEdges(MD::Edges(20, 100, 20, 100));
            layer->setColor(1, 0, 0);
            layer->setXRange({0, CGFloat(line->size())});
            layer->setYRange({0, 10});
            layer->setLine(line);
            canvas->AddLayer(layer);
        });
    }
}

- (void)setLines:(std::shared_ptr<MD::View::Lines>)lines {
    _lines = lines;
    
    [self setNeedsRebuildCanvas];
}

@end
