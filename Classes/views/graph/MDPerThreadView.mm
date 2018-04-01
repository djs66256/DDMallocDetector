//
//  MDPerThreadView.m
//  DDMallocDetector
//
//  Created by daniel on 2018/4/1.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include <strstream>
#import "MDPerThreadView.h"
#include "StrokeLayer.hpp"

typedef MD::PairStrokeLayer<time_t, std::size_t> TimeSizeLayer;

@implementation MDPerThreadView {
    MD::PerThreadData::memory_list_type_ptr _lines;
    std::shared_ptr<TimeSizeLayer> _lineLayer;
    double _minX;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _lineLayer = std::make_shared<TimeSizeLayer>();
        _lineLayer->setEdges(MD::Edges(20, 100, 20, 100));
        _lineLayer->setColor(1, 0, 0);
        
        _xAxis->setName("Time");
        _xAxis->setEdges(MD::Edges(20, 100, 20, 100));
        
        _yAxis->setName("Mem(log2)");
        _yAxis->setEdges(MD::Edges(20, 100, 20, 100));
        
        _contentLayer->setEdges(MD::Edges(20, 100, 20, 100));
        _contentLayer->setBackgroundColor({0.2, 0.2, 0.2});
        
        _yAxis->anchors().setFormatter([](auto f) {
            std::strstream s;
            s << "2^" << f;
            return s.str();
        });
        
        __weak typeof(self) weakSelf = self;
        _xAxis->anchors().setFormatter([weakSelf](auto f) -> const char* {
            if (weakSelf) {
                __strong typeof(weakSelf) strongSelf = weakSelf;
                double min = strongSelf->_minX;
                std::strstream s;
                s << int((f - min)/1000);
                return s.str();
            }
            return "";
        });
    }
    return self;
}

- (void)setPerThreadData:(const MD::PerThreadData::ThreadInfo &)data {
    if (data.memory->size() > 2) {
        _lines = data.memory;
        _lineLayer->setLine(_lines);
        _lineLayer->setXRange({CGFloat(_lines->at(0).first), CGFloat(_lines->at(_lines->size() - 1).first)});
        _lineLayer->setYRange({CGFloat(data.min.second), CGFloat(data.max.second)});
        _minX = data.min.first;
        
        _xAxis->setRange(data.min.first, data.max.first);
        _yAxis->setRange(data.min.second, data.max.second);
        [self setNeedsRebuildCanvas];
    }
}

- (void)rebuildCanvas {
    [super rebuildCanvas];
    
    auto cvs = [self canvas];
    cvs->AddLayer(_lineLayer);
}

@end
