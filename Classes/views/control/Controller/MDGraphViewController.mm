//
//  MDGraphViewController.m
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDGraphViewController.h"

@interface MDGraphViewController ()

@end

@implementation MDGraphViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.statView = [[MDStatisticsView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:self.statView];
    
    auto line = std::make_shared<MD::View::Line>();
    line->push_back(2);
    line->push_back(3);
    line->push_back(6);
    line->push_back(4);
    line->push_back(9);
    line->push_back(6);
    line->push_back(1);
    line->push_back(3);
    
    auto lines = std::make_shared<MD::View::Lines>();
    lines->emplace_back(line);
    
    [self.statView setLines:lines];
    [self.statView rebuildCanvasIfNeeded];
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
