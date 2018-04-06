//
//  MDGraphViewController.h
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MDPerThreadView.h"

@interface MDByThreadGraphViewController : UIViewController

@property (nonatomic, strong) MDPerThreadView *statView;

- (void)setData:(MD::PerThreadData::memory_list_type_ptr)data;

@end
