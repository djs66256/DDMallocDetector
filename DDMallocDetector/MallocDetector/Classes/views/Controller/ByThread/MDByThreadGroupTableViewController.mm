//
//  MDByThreadGroupTableViewController.m
//  DDMallocDetector
//
//  Created by daniel on 2018/4/3.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDByThreadGroupTableViewController.h"
#import "../../../analysis/AnalysisPerThread.hpp"
#import "MDByThreadGraphViewController.h"

@interface MDByThreadGroupTableViewController () {
    std::shared_ptr<MD::PerThreadData> _data;
}

@end

@implementation MDByThreadGroupTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.tableView registerClass:UITableViewCell.class forCellReuseIdentifier:@"cell"];
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        MD::AnalysisPerThread a;
        a.Start();
        auto data = a.data();
//        auto threadInfo = data->thread_memory()[0];
//        typedef MD::PerThreadData::memory_info_type T;
//        CompositeNormalize<T> parser(threadInfo.memory);
//        parser.then(Compress<T>(256*4)).then(Scale<T>().scale([](auto& v){
//            if (v.second > 0) {
//                v.second = log2(v.second/8);
//            }
//            else {
//                v.second = 0;
//            }
//        }));
//        threadInfo.memory = parser.list();
//
//        threadInfo.min = {threadInfo.memory->at(0).first, 0};
//        threadInfo.max = {threadInfo.memory->at(threadInfo.memory->size() - 1).first, log(1024*1024*100)};
        
        dispatch_async(dispatch_get_main_queue(), ^{
            _data = data;
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
        return 2;
    }
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    switch (section) {
        case 0:
            return 1;
        case 1:
            return _data->thread_memory().size();
    }
    return 0;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell" forIndexPath:indexPath];
    
    switch (indexPath.section) {
        case 0:{
            cell.textLabel.text = @"全部";
        }
            break;
        case 1:{
            cell.textLabel.text = [NSString stringWithCString:_data->thread_memory()[indexPath.row].name.c_str() encoding:NSUTF8StringEncoding];
        }
            break;
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    switch (indexPath.section) {
        case 0:{
            
        }
            break;
        case 1:{
            MDByThreadGraphViewController *vc = [MDByThreadGraphViewController new];
            vc.title = [NSString stringWithFormat:@"%s", _data->thread_memory().at(indexPath.row).name.c_str()];
            [vc setData:_data->thread_memory()[indexPath.row].memory];
            [self.navigationController pushViewController:vc animated:YES];
        }
            break;
    }
}

@end
