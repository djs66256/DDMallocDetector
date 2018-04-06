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

//typedef MD::LinearAnchors<double> ByTimeAnchors;
//typedef MD::DiscreteAnchors<MDByTimeItemType> ByTimeDiscreteAnchors;
//typedef std::shared_ptr<ByTimeAnchors> BySizeAnchorsPtr;
//typedef std::shared_ptr<ByTimeDiscreteAnchors> BySizeDiscreteAnchorsPtr;

typedef MD::XAxisLayer<MD::DiscreteAnchors<MDByTimeItemType>> XAxisLayerType;
typedef MD::YAxisLayer<MD::LinearAnchors<double>> YAxisLayerType;

@implementation MDByTimeView {
    MDByTimeDataPtrType _data;
    std::shared_ptr<MDByTimeViewLayer> _strokeLayer;
    double _max;
    
    std::shared_ptr<XAxisLayerType> _xAxisLayer;
    std::shared_ptr<YAxisLayerType> _yAxisLayer;
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
        
        _xAxisLayer->anchors().setMaxCount(16);
        _xAxisLayer->anchors().setFormatter([](auto& v) {
            std::strstream s;
            if (v.first >= 1024 * 1024) {
                s << std::setprecision(0) << std::fixed << double(v.first) / 1024 / 1024 << "M";
            }
            else if (v.first >= 1024) {
                s << std::setprecision(0) << std::fixed << double(v.first) / 1024 << "K";
            }
            else {
                s << v.first;
            }
            return s.str();
        });
        
        _yAxisLayer->anchors().setFormatter([](auto v) {
            std::strstream s;
            s << std::setprecision(1) << std::fixed << v;
            return s.str();
        });
    }
    return self;
}

- (std::shared_ptr<MD::AxisLayer>)makeYAxis {
    _yAxisLayer = std::make_shared<YAxisLayerType>();
    return _yAxisLayer;
}

- (std::shared_ptr<MD::AxisLayer>)makeXAxis {
    _xAxisLayer = std::make_shared<XAxisLayerType>();
    return _xAxisLayer;
}

- (void)setData:(MDByTimeDataPtrType)data {
    _data = data;
    
    _max = 0;
    std::for_each(data->begin(), data->end(), [&](auto& p) {
        _max = std::max(p.second, _max);
    });
    _max = ceil(_max/10)*10;
    
    _xAxisLayer->anchors().setPoints(data);
    _yAxisLayer->anchors().setRange(0, _max);
    
    _strokeLayer->setLine(data);
    _strokeLayer->setXRange(data->at(0).first, data->at(data->size() - 1).first);
    _strokeLayer->setYRange(0, _max);
    
    [self setNeedsRebuildCanvas];
}

- (void)rebuildCanvas {
    [super rebuildCanvas];
    
    auto cvs = [self canvas];
    cvs->AddLayer(_strokeLayer);
    cvs->AddLayer(_xAxis);
    cvs->AddLayer(_yAxis);
}

@end
