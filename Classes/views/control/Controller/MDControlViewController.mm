//
//  MDControlViewController.m
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDControlViewController.h"
#import "MDGraphViewController.h"
#import "MDInspectorIcon.h"

@interface MDControlViewController ()
@property (nonatomic, strong) MDInspectorIcon *icon;
@end

@implementation MDControlViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.icon = [[MDInspectorIcon alloc] initWithFrame:CGRectMake(0, 100, 40, 40)];
    [self.icon addTarget:self action:@selector(onIcon:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:self.icon];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = YES;
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    self.navigationController.navigationBarHidden = NO;
}

- (void)onIcon:(id)sender {
    MDGraphViewController *vc = [MDGraphViewController new];
    [self.navigationController pushViewController:vc animated:YES];
}

@end
