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
    std::size_t _maxY;
}

@property (nonatomic, strong) MDBySizeView *graphView;

@end

@implementation MDBySizeGraphViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.graphView = [[MDBySizeView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:self.graphView];
    
    [self.graphView setList:_data minCount:0 maxCount:_maxY];
    [self.graphView rebuildCanvasIfNeeded];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void)setData:(MDBySizeGraphViewControllerData)data {
    _data = data;
    
    std::size_t max = 0;
    std::for_each(_data->begin(), _data->end(), [&](auto& p) {
        max = std::max(max, p.second);
    });
    _maxY = ceil(double(max) / 1000) * 1000;
    
//    [self printData];
    if (self.graphView) {
        [self.graphView setList:_data minCount:0 maxCount:_maxY];
        [self.graphView rebuildCanvasIfNeeded];
    }
}

- (void)printData {
    std::for_each(_data->begin(), _data->end(), [](auto& p) {
        printf("(%ld, %ld)\n", p.first, p.second);
    });
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
