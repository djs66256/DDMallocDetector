//
//  MDPerThreadView.m
//  DDMallocDetector
//
//  Created by daniel on 2018/4/1.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDPerThreadView.h"
#include "StrokeLayer.hpp"

typedef MD::PairStrokeLayer<time_t, std::size_t> TimeSizeLayer;

@implementation MDPerThreadView {
    MD::PerThreadData::memory_list_type_ptr _lines;
    std::shared_ptr<TimeSizeLayer> _lineLayer;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _lineLayer = std::make_shared<TimeSizeLayer>();
        _lineLayer->setEdges(MD::Edges(20, 100, 20, 100));
        _lineLayer->setColor(1, 0, 0);
        
        _xAxis->setEdges(MD::Edges(20, 100, 20, 100));
        _yAxis->setEdges(MD::Edges(20, 100, 20, 100));
        _contentLayer->setEdges(MD::Edges(20, 100, 20, 100));
        _contentLayer->setBackgroundColor({0.2, 0.2, 0.2});
    }
    return self;
}

- (void)setPerThreadData:(const MD::PerThreadData::ThreadInfo &)data {
    if (data.memory->size() > 2) {
        _lines = data.memory;
        _lineLayer->setLine(_lines);
        _lineLayer->setXRange({CGFloat(_lines->at(0).first), CGFloat(_lines->at(_lines->size() - 1).first)});
        _lineLayer->setYRange({CGFloat(data.min.second), CGFloat(data.max.second)});
        [self setNeedsRebuildCanvas];
    }
}

- (void)rebuildCanvas {
    [super rebuildCanvas];
    
    auto cvs = [self canvas];
    cvs->AddLayer(_lineLayer);
}

@end
