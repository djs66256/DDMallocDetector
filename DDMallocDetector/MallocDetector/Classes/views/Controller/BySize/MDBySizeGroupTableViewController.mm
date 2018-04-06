//
//  MDBySizeGroupTableViewController.m
//  DDMallocDetector
//
//  Created by hzduanjiashun on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDBySizeGroupTableViewController.h"
#import "MDBySizeGraphViewController.h"
#import "MDBySizeGenerateTableViewController.h"
#include "../../../analysis/AnalysisBySize.hpp"

@interface MDBySizeGroupTableViewController () {
    std::shared_ptr<MD::AnalysisBySize<>::thread_info_list_type> _data;
    std::shared_ptr<MD::AnalysisBySize<>::list_type> _allData;
}

@end

@implementation MDBySizeGroupTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"cell"];
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        MD::AnalysisBySize<> a(1, 8*1024*1024); // 8 bytes ~ 8M
        a.Start();
        
        auto data = a.data();
        _data = data;
        
        _allData = std::make_shared<MD::AnalysisBySize<>::list_type>();
        
        std::for_each(data->begin(), data->end(), [&](auto& threadInfo) {
            for (int i = 0; i < threadInfo.list->size(); ++i) {
                auto& p = threadInfo.list->at(i);
                if (i >= _allData->size()) {
                    _allData->push_back(std::pair<std::size_t, std::size_t>(p.first, 0));
                }
                _allData->at(i).second += p.second;
            }
        });
        
        dispatch_async(dispatch_get_main_queue(), ^{
//            auto line = data->at(0).list;
            
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
    }
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell" forIndexPath:indexPath];
    
    if (indexPath.section == 0) {
        cell.textLabel.text = @"统计";
    }
    else if (indexPath.section == 1) {
        cell.textLabel.text = @"全部";
    }
    else if (indexPath.section == 2) {
        auto threadInfo = _data->at(indexPath.row);
        
        cell.textLabel.text = [NSString stringWithCString:threadInfo.name.c_str() encoding:NSUTF8StringEncoding];
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.section == 0) {
        MDBySizeGenerateTableViewController *vc = [MDBySizeGenerateTableViewController new];
        [self.navigationController pushViewController:vc animated:YES];
    }
    else if (indexPath.section == 1) {
        MDBySizeGraphViewController *vc = [MDBySizeGraphViewController new];
        vc.title = @"全部";
        [vc setData:_allData];
        [self.navigationController pushViewController:vc animated:YES];
    }
    else if (indexPath.section == 2) {
        MDBySizeGraphViewController *vc = [MDBySizeGraphViewController new];
        vc.title = [NSString stringWithFormat:@"%s", _data->at(indexPath.row).name.c_str()];
        [vc setData:_data->at(indexPath.row).list];
        [self.navigationController pushViewController:vc animated:YES];
    }
}

@end
