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
                      }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.data.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell" forIndexPath:indexPath];
    
    cell.textLabel.text = self.data[indexPath.row][@"title"];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    Class cls = self.data[indexPath.row][@"class"];
    UIViewController *vc = [[cls alloc] init];
    vc.title = self.data[indexPath.row][@"title"];
    [self.navigationController pushViewController:vc animated:YES];
}

@end
