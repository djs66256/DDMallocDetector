//
//  MDGraphViewController.m
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#import "MDGraphViewController.h"
#import "../../analysis/AnalysisPerThread.hpp"
#import "../../base/Normalize.hpp"

using namespace MD::Normalize;

@interface MDGraphViewController ()

@end

@implementation MDGraphViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.statView = [[MDPerThreadView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:self.statView];
    
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
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        MD::AnalysisPerThread a;
        a.Start();
        auto data = a.data();
        auto threadInfo = data->thread_memory()[0];
        typedef MD::PerThreadData::memory_info_type T;
        CompositeNormalize<T> parser(threadInfo.memory);
        parser.then(Compress<T>(256*4)).then(Scale<T>().scale([](auto& v){
            if (v.second > 0) {
                v.second = log2(v.second/8);
            }
            else {
                v.second = 0;
            }
        }));
        threadInfo.memory = parser.list();
        
//        threadInfo.max = threadInfo.min = *(threadInfo.memory->begin());
//        std::for_each(threadInfo.memory->begin(), threadInfo.memory->end(), [&](auto& i) {
//            if (threadInfo.max.second < i.second) {
//                threadInfo.max = i;
//            }
//            if (threadInfo.min.second > i.second) {
//                threadInfo.min = i;
//            }
//        });
        
        threadInfo.min = {threadInfo.memory->at(0).first, 0};
        threadInfo.max = {threadInfo.memory->at(threadInfo.memory->size() - 1).first, log(1024*1024*100)};
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.statView setPerThreadData:threadInfo];
            [self.statView rebuildCanvasIfNeeded];
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
