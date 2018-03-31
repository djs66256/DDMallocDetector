//
//  AnalysisTaskRunner.hpp
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef AnalysisTaskRunner_hpp
#define AnalysisTaskRunner_hpp

#include <stdio.h>
#include <functional>
#include <thread>
#include "AnalysisTask.hpp"

namespace MD {
    class AnalysisTaskRunner final {
    public:
        void run(AnalysisTask&& task, std::function<void(AnalysisTask&& task)> complete);
        
    private:
        AnalysisTaskRunner() : thread_([this](){ this->main(); }) {}
        void main();
        
        std::thread thread_;
    };
}

#endif /* AnalysisTaskRunner_hpp */
