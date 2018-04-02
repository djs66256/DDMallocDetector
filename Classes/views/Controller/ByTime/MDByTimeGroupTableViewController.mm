//
//  MDByTimeGroupTableViewController.m
//  DDMallocDetector
//
//  Created by daniel on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDByTimeGroupTableViewController.h"
#import "MDByTimeGraphViewController.h"
#include "../../../analysis/AnalysisByTime.hpp"

@interface MDByTimeGroupTableViewController () {
    MD::AnalysisByTime<>::thread_list_type_ptr _data;
    MD::AnalysisByTime<>::list_type_ptr _all_list;
}

@end

@implementation MDByTimeGroupTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.tableView registerClass:UITableViewCell.class forCellReuseIdentifier:@"cell"];
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        MD::AnalysisByTime<> a(0, 1024*1024);
        a.Start();
        
        auto data = a.data();
        auto all_list = a.all_list();
        dispatch_async(dispatch_get_main_queue(), ^{
            _data = data;
            _all_list = all_list;
        
#if 1
            std::for_each(_data->begin(), _data->end(), [](auto& t) {
                t.Print();
            });
#endif
            [self.tableView reloadData];
        });
    });
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    if (_data) {
        return 3;
    }
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    switch (section) {
        case 0:
        case 1:
            return 1;
        case 2:
            return _data->size();
            
        default:
            break;
    }
    return 0;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell" forIndexPath:indexPath];
    
    switch (indexPath.section) {
        case 0:
            cell.textLabel.text = @"统计";
            break;
        case 1:
            cell.textLabel.text = @"全部线程";
            break;
        case 2: {
            auto threadInfo = _data->at(indexPath.row);
            cell.textLabel.text = [NSString stringWithCString:threadInfo.name.c_str() encoding:NSUTF8StringEncoding];
        }
            break;
            
        default:
            break;
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    switch (indexPath.section) {
        case 0:
            break;
        case 1: {
            MDByTimeGraphViewController *vc = [MDByTimeGraphViewController new];
            [vc setData:_all_list];
            [self.navigationController pushViewController:vc animated:YES];
        }
            break;
        case 2: {
            MDByTimeGraphViewController *vc = [MDByTimeGraphViewController new];
            [vc setData:_data->at(indexPath.row).list];
            [self.navigationController pushViewController:vc animated:YES];
        }
            break;
            
        default:
            break;
    }
}

@end
