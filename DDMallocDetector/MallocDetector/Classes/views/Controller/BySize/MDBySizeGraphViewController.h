//
//  MDBySizeGraphViewController.h
//  DDMallocDetector
//
//  Created by daniel on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "../../../analysis/AnalysisBySize.hpp"

typedef std::shared_ptr<std::vector<std::pair<std::size_t, std::size_t>>> MDBySizeGraphViewControllerData;

@interface MDBySizeGraphViewController : UIViewController

- (void)setData:(MDBySizeGraphViewControllerData)data;

@end
