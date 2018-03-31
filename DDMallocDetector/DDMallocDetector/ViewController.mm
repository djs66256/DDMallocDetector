//
//  ViewController.m
//  DDMallocDetector
//
//  Created by hzduanjiashun on 2018/3/30.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "ViewController.h"
#import "MDStatisticsView.h"
#import "MDInspectorWindow.h"

@interface ViewController ()

@property (nonatomic, strong) MDStatisticsView *statView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [MDInspectorWindow enable];
//
//    self.statView = [[MDStatisticsView alloc] initWithFrame:self.view.bounds];
//    [self.view addSubview:self.statView];
//
//    auto line = std::make_shared<MD::View::Line>();
//    line->push_back(2);
//    line->push_back(3);
//    line->push_back(6);
//    line->push_back(4);
//    line->push_back(9);
//    line->push_back(6);
//    line->push_back(1);
//    line->push_back(3);
//
//    auto lines = std::make_shared<MD::View::Lines>();
//    lines->emplace_back(line);
//
//    [self.statView setLines:lines];
//    [self.statView rebuildCanvasIfNeeded];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
