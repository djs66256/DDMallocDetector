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

@interface MDBySizeGraphViewController ()

@property (nonatomic, strong) MDBySizeView *graphView;

@end

@implementation MDBySizeGraphViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.graphView = [[MDBySizeView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:self.graphView];
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        MD::AnalysisBySize<MD::StepByLog<2, 1>> a(8, 8*1024*1024); // 8 bytes ~ 8M
        a.Start();
        
        auto data = a.data();
        
        dispatch_async(dispatch_get_main_queue(), ^{
            auto line = data->at(0).list;
//            printf("%ld", line->size());
            [self.graphView setList:line minCount:0 maxCount:10000];
            [self.graphView rebuildCanvasIfNeeded];
        });
    });
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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
