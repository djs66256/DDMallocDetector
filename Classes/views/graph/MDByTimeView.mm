//
//  MDByTimeView.m
//  DDMallocDetector
//
//  Created by daniel on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDByTimeView.h"
#include "StrokeLayer.hpp"
#include <strstream>
#include <iomanip>

typedef MD::PairLinearStrokeLayer<std::size_t, double> MDByTimeViewLayer;

typedef MD::LinearAnchors<std::size_t> ByTimeAnchors;
typedef MD::DiscreteAnchors<MDByTimeItemType> ByTimeDiscreteAnchors;
typedef std::shared_ptr<ByTimeAnchors> BySizeAnchorsPtr;
typedef std::shared_ptr<ByTimeDiscreteAnchors> BySizeDiscreteAnchorsPtr;

@implementation MDByTimeView {
    MDByTimeDataPtrType _data;
    std::shared_ptr<MDByTimeViewLayer> _strokeLayer;
    BySizeDiscreteAnchorsPtr _xAnchors;
    BySizeAnchorsPtr _yAnchors;
    double _max;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _strokeLayer = std::make_shared<MDByTimeViewLayer>();
        _strokeLayer->setEdges(MD::Edges(20, 100, 20, 100));
        _strokeLayer->setColor(1, 0, 0);
        
        
        _xAxis->setName("Size");
        _yAxis->setName("time_t");
        
        _xAnchors = std::make_shared<ByTimeDiscreteAnchors>();
        _xAnchors->setMaxCount(16);
        _xAnchors->setFormatter([](auto& v) {
            std::strstream s;
            if (v.first >= 1024 * 1024) {
                s << std::setprecision(1) << std::fixed << double(v.first) / 1024 / 1024 << "M";
            }
            else if (v.first >= 1024) {
                s << std::setprecision(1) << std::fixed << double(v.first) / 1024 << "K";
            }
            else {
                s << v.first;
            }
            return s.str();
        });
        _xAxis->setAnchors(_xAnchors);
        
        _yAnchors = std::make_shared<ByTimeAnchors>();
        _yAxis->setAnchors(_yAnchors);
    }
    return self;
}

- (void)setData:(MDByTimeDataPtrType)data {
    _data = data;
    
    _max = 0;
    std::for_each(data->begin(), data->end(), [&](auto& p) {
        _max = std::max(p.second, _max);
    });
    
    _xAnchors->setPoints(data);
    _yAnchors->setRange(0, _max);
    
    _strokeLayer->setLine(data);
    _strokeLayer->setXRange(data->at(0).first, data->at(data->size() - 1).first);
    _strokeLayer->setYRange(0, _max);
    
    [self setNeedsRebuildCanvas];
}

- (void)rebuildCanvas {
    [super rebuildCanvas];
    
    auto cvs = [self canvas];
    cvs->AddLayer(_strokeLayer);
}

@end
