//
//  MDByTimeGraphViewController.m
//  DDMallocDetector
//
//  Created by daniel on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDByTimeGraphViewController.h"

@interface MDByTimeGraphViewController () {
    MDByTimeDataPtrType _data;
}

@property (nonatomic, strong) MDByTimeView *graphView;

@end

@implementation MDByTimeGraphViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.graphView = [[MDByTimeView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:self.graphView];
    
    [self.graphView setData:_data];
    [self.graphView rebuildCanvasIfNeeded];
}

- (void)setData:(MDByTimeDataPtrType)data {
    _data = data;
    
    [self.graphView setData:_data];
    [self.graphView rebuildCanvasIfNeeded];
}

@end
