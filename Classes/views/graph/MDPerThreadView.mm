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
        
        _yAxis->setName("Mem(log2)");
        
//        _yAxis->anchors().setFormatter([](auto f) {
//            std::strstream s;
//            s << "2^" << f;
//            return s.str();
//        });
//
//        __weak typeof(self) weakSelf = self;
//        _xAxis->anchors().setFormatter([weakSelf](auto f) -> const char* {
//            if (weakSelf) {
//                __strong typeof(weakSelf) strongSelf = weakSelf;
//                double min = strongSelf->_minX;
//                std::strstream s;
//                s << int((f - min)/1000);
//                return s.str();
//            }
//            return "";
//        });
    }
    return self;
}

- (void)setPerThreadData:(MD::PerThreadData::memory_list_type_ptr)data {
    if (data->size() > 2) {
        _lines = data;
        _lineLayer->setLine(_lines);
        _lineLayer->setXRange({CGFloat(_lines->at(0).first), CGFloat(_lines->at(_lines->size() - 1).first)});
        
        CGFloat max = log(1024*1024*100);
        _lineLayer->setYRange({CGFloat(0), CGFloat(max)});
        _minX = CGFloat(_lines->at(0).first);
        
        [self setNeedsRebuildCanvas];
    }
}

- (void)rebuildCanvas {
    [super rebuildCanvas];
    
    auto cvs = [self canvas];
    cvs->AddLayer(_lineLayer);
}

@end
