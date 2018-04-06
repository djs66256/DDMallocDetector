//
//  MDBySizeView.m
//  DDMallocDetector
//
//  Created by daniel on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDBySizeView.h"
#import "StrokeLayer.hpp"
#include <strstream>
#include <iomanip>

typedef MD::PairLinearStrokeLayer<std::size_t, std::size_t> BySizeLayer;
//typedef MD::LinearAnchors<std::size_t> BySizeAnchors;
//typedef MD::DiscreteAnchors<MDBySizeItemType> BySizeDiscreteAnchors;
//typedef std::shared_ptr<BySizeAnchors> BySizeAnchorsPtr;
//typedef std::shared_ptr<BySizeDiscreteAnchors> BySizeDiscreteAnchorsPtr;

typedef MD::XAxisLayer<MD::DiscreteAnchors<MDBySizeItemType>> XAxisLayerType;
typedef MD::YAxisLayer<MD::LinearAnchors<std::size_t>> YAxisLayerType;

@implementation MDBySizeView {
    MDBySizeListType _list;
    std::shared_ptr<BySizeLayer> _strokeLayer;
//    BySizeDiscreteAnchorsPtr _xAnchors;
//    BySizeAnchorsPtr _yAnchors;
    
    std::shared_ptr<XAxisLayerType> _xAxisLayer;
    std::shared_ptr<YAxisLayerType> _yAxisLayer;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _strokeLayer = std::make_shared<BySizeLayer>();
        _strokeLayer->setEdges(MD::Edges(20, 100, 20, 100));
        _strokeLayer->setColor(1, 0, 0);
        
        _xAxis->setName("Size");
        _yAxis->setName("Count / K");
        
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
        
        _yAxisLayer->anchors().setFormatter([](auto f) -> const char* {
            if (f < 0.01) {
                return "0";
            }
            std::strstream s;
            s << std::setprecision(1) << std::fixed << f/1000;
            return s.str();
        });
        
    }
    return self;
}

- (std::shared_ptr<MD::AxisLayer>)makeXAxis {
    _xAxisLayer = std::make_shared<XAxisLayerType>();
    return _xAxisLayer;
}

- (std::shared_ptr<MD::AxisLayer>)makeYAxis {
    _yAxisLayer = std::make_shared<YAxisLayerType>();
    return _yAxisLayer;
}

- (void)setList:(MDBySizeListType)list minCount:(std::size_t)min maxCount:(std::size_t)max {
    _list = list;
    
    _strokeLayer->setLine(list);
    _strokeLayer->setYRange(min, max);
    _strokeLayer->setXRange(0, ULONG_MAX);
    
    _xAxisLayer->anchors().setPoints(list);
    
    _yAxisLayer->anchors().setRange(min, max);
    
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
