//
//  MDBySizeView.h
//  DDMallocDetector
//
//  Created by daniel on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDDrawableView.h"
#include <vector>
#include <memory>
#include <cmath>

typedef std::pair<std::size_t, std::size_t> MDBySizeItemType;
typedef std::shared_ptr<std::vector<MDBySizeItemType>> MDBySizeListType;

@interface MDBySizeView : MDDrawableView

- (void)setList:(MDBySizeListType)list minCount:(std::size_t)min maxCount:(std::size_t)max;

@end
