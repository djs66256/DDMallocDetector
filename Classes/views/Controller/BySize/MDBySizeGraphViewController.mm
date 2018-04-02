//
//  MDBySizeGraphViewController.m
//  DDMallocDetector
//
//  Created by daniel on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDBySizeGraphViewController.h"
#import "AnalysisBySize.hpp"
#import "MDBySizeView.h"
#import "convertor.h"

@interface MDBySizeGraphViewController () {
    MDBySizeGraphViewControllerData _data;
}

@property (nonatomic, strong) MDBySizeView *graphView;

@end

@implementation MDBySizeGraphViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.graphView = [[MDBySizeView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:self.graphView];
    
    [self.graphView setList:_data minCount:0 maxCount:5000];
    [self.graphView rebuildCanvasIfNeeded];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void)setData:(MDBySizeGraphViewControllerData)data {
    _data = data;
    if (self.graphView) {
        [self.graphView setList:_data minCount:0 maxCount:5000];
        [self.graphView rebuildCanvasIfNeeded];
    }
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
