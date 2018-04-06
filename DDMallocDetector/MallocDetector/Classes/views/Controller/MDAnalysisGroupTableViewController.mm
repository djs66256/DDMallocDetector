//
//  MDAnalysisGroupTableViewController.m
//  DDMallocDetector
//
//  Created by hzduanjiashun on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDAnalysisGroupTableViewController.h"
#import "MDBySizeGroupTableViewController.h"
#import "MDByTimeGroupTableViewController.h"
#import "MDByThreadGroupTableViewController.h"
#import "../../detector/MemoryDetector.hpp"

@interface MDAnalysisGroupTableViewController ()
@property (nonatomic, strong) NSArray *data;
@end

@implementation MDAnalysisGroupTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.tableView registerClass:UITableViewCell.class forCellReuseIdentifier:@"cell"];
    
    self.data = @[@{
                      @"class": MDBySizeGroupTableViewController.class,
                      @"title": @"大小分析"
                    },
                  @{
                      @"class": MDByTimeGroupTableViewController.class,
                      @"title": @"时间分析"
                      },
                  @{
                      @"class": MDByThreadGroupTableViewController.class,
                      @"title": @"按申请顺序"
                      }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 2;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == 0) {
        return 1;
    }
    else {
        return self.data.count;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell" forIndexPath:indexPath];
    
    if (indexPath.section == 0) {
        cell.textLabel.text = @"restart";
    }
    else {
        cell.textLabel.text = self.data[indexPath.row][@"title"];
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.section == 0) {
        [self.navigationController popViewControllerAnimated:YES];
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            MD::MemoryDetector::GetInstance()->ClearPool();
            MD::MemoryDetector::GetInstance()->Start();
        });
    }
    else {
        Class cls = self.data[indexPath.row][@"class"];
        UIViewController *vc = [[cls alloc] init];
        vc.title = self.data[indexPath.row][@"title"];
        [self.navigationController pushViewController:vc animated:YES];
    }
}

@end
