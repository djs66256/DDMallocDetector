//
//  MDPerThreadView.h
//  DDMallocDetector
//
//  Created by daniel on 2018/4/1.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDDrawableView.h"
#include "AnalysisPerThread.hpp"

@interface MDPerThreadView : MDDrawableView

- (void)setPerThreadData:(const MD::PerThreadData::ThreadInfo &)data;

@end
