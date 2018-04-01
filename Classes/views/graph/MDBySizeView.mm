//
//  MDBySizeView.m
//  DDMallocDetector
//
//  Created by daniel on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDBySizeView.h"
#import "StrokeLayer.hpp"

typedef MD::PairLinearStrokeLayer<std::size_t, std::size_t> BySizeLayer;

@implementation MDBySizeView {
    MDBySizeListType _list;
    std::shared_ptr<BySizeLayer> _strokeLayer;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _strokeLayer = std::make_shared<BySizeLayer>();
        _strokeLayer->setEdges(MD::Edges(20, 100, 20, 100));
        _strokeLayer->setColor(1, 0, 0);
        
    }
    return self;
}

- (void)setList:(MDBySizeListType)list minCount:(std::size_t)min maxCount:(std::size_t)max {
    _list = list;
    
    _strokeLayer->setLine(list);
    _strokeLayer->setYRange(min, max);
    _strokeLayer->setXRange(0, ULONG_MAX);
    
    [self setNeedsRebuildCanvas];
}

- (void)rebuildCanvas {
    [super rebuildCanvas];
    
    auto cvs = [self canvas];
    cvs->AddLayer(_strokeLayer);
}

@end
