//
//  MDStatisticsView.h
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/29.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MDDrawableView.h"
#include <vector>
#include <memory>

namespace MD {
    namespace View {
        typedef std::vector<int64_t> Line;
        typedef std::vector<std::shared_ptr<Line>> Lines;
    }
}

@interface MDStatisticsView : MDDrawableView

- (void)setLines:(std::shared_ptr<MD::View::Lines>)lines;
- (void)rebuildCanvasIfNeeded;

@end
