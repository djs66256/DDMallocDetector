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
typedef MD::LinearAnchors<std::size_t> BySizeAnchors;
typedef MD::DiscreteAnchors<MDBySizeItemType> BySizeDiscreteAnchors;
typedef std::shared_ptr<BySizeAnchors> BySizeAnchorsPtr;
typedef std::shared_ptr<BySizeDiscreteAnchors> BySizeDiscreteAnchorsPtr;

@implementation MDBySizeView {
    MDBySizeListType _list;
    std::shared_ptr<BySizeLayer> _strokeLayer;
    BySizeDiscreteAnchorsPtr _xAnchors;
    BySizeAnchorsPtr _yAnchors;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _strokeLayer = std::make_shared<BySizeLayer>();
        _strokeLayer->setEdges(MD::Edges(20, 100, 20, 100));
        _strokeLayer->setColor(1, 0, 0);
        
        _contentLayer->setEdges(MD::Edges(20, 100, 20, 100));
        _contentLayer->setBackgroundColor({0.8, 0.8, 0.8});
        
        _xAxis->setName("Size");
        _xAxis->setEdges(MD::Edges(20, 100, 20, 100));
        
        
        _yAxis->setName("Count");
        _yAxis->setEdges(MD::Edges(20, 100, 20, 100));
        
        _xAnchors = std::make_shared<BySizeDiscreteAnchors>();
        _xAnchors->setMaxCount(10);
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
        
        _yAnchors = std::make_shared<BySizeAnchors>();
        _yAnchors->setFormatter([](auto f) -> const char* {
            printf("%f\n", f);
            if (f < 0.01) {
                return "0";
            }
            std::strstream s;
            s << std::setprecision(1) << std::fixed << f/1000 << "k";
            return s.str();
        });
        _yAxis->setAnchors(_yAnchors);
        
    }
    return self;
}

//- (void)setXMin:(std::size_t)min max:(std::size_t)max {
//    _xAxis->setRange(min, max);
//}

- (void)setList:(MDBySizeListType)list minCount:(std::size_t)min maxCount:(std::size_t)max {
    _list = list;
    
    _strokeLayer->setLine(list);
    _strokeLayer->setYRange(min, max);
    _strokeLayer->setXRange(0, ULONG_MAX);
    
//    auto anchors = std::make_shared<std::vector<std::size_t>>();
//    std::for_each(list->begin(), list->end(), [&](auto& i) {
//        anchors->push_back(i.first);
//    });
    _xAnchors->setPoints(list);
    
    _yAnchors->setRange(min, max);
//    _yAxis->setRange(min, max);
    
    [self setNeedsRebuildCanvas];
}

- (void)rebuildCanvas {
    [super rebuildCanvas];
    
    auto cvs = [self canvas];
    cvs->AddLayer(_strokeLayer);
}

@end
