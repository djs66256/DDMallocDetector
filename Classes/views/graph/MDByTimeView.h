//
//  MDByTimeView.h
//  DDMallocDetector
//
//  Created by daniel on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDDrawableView.h"
#include <vector>
#include <memory>

typedef std::pair<std::size_t, double> MDByTimeItemType;
typedef std::vector<MDByTimeItemType> MDByTimeDataType;
typedef std::shared_ptr<MDByTimeDataType> MDByTimeDataPtrType;

@interface MDByTimeView : MDDrawableView

- (void)setData:(MDByTimeDataPtrType)data;

@end
