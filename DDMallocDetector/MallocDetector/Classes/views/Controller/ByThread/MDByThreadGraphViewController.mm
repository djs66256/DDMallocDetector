//
//  MDGraphViewController.m
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDByThreadGraphViewController.h"
#import "../../../base/Normalize.hpp"

using namespace MD::Normalize;

@interface MDByThreadGraphViewController () {
    MD::PerThreadData::memory_list_type_ptr _data;
}

@end

@implementation MDByThreadGraphViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.statView = [[MDPerThreadView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:self.statView];
    
    if (_data) {
        [self.statView setPerThreadData:_data];
        [self.statView rebuildCanvasIfNeeded];
    }
}


- (void)setData:(MD::PerThreadData::memory_list_type_ptr)data {
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        typedef MD::PerThreadData::memory_info_type T;
        CompositeNormalize<T> parser(data);
        parser.then(Compress<T>(256*4)).then(Scale<T>().scale([](auto& v){
            if (v.second > 0) {
                v.second = log2(v.second/8);
            }
            else {
                v.second = 0;
            }
        }));
        auto list = parser.list();
        
        dispatch_async(dispatch_get_main_queue(), ^{
            _data = list;
            [self.statView setPerThreadData:_data];
            [self.statView rebuildCanvasIfNeeded];
        });
    });
}

@end
